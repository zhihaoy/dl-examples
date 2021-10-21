#pragma once

#include <Windows.h>
#include <libloaderapi.h>

#include <filesystem>
#include <memory>
#include <system_error>
#include <type_traits>
#include <utility>

namespace plugindemo
{

template <class T> inline auto transfer_module(T *key)
{
    struct library_deleter
    {
        void operator()(T *lib) const noexcept
        {
            ::FreeLibrary(lib);
        }
    };

    return std::unique_ptr<T, library_deleter>(key);
}

template <class Factory> class plugin
{
    decltype(transfer_module(HMODULE())) lib_;
    Factory *obj_;

  public:
    explicit plugin(std::filesystem::path const &dll)
        : lib_([&] {
              if (auto lib = ::LoadLibraryExW(dll.c_str(), nullptr,
                                              LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR))
                  return transfer_module(lib);
              else
                  throw std::system_error(GetLastError(), std::system_category());
          }()),
          obj_([this] {
              if (auto pinst = (Factory *)::GetProcAddress(lib_.get(), "instance"))
                  return pinst;
              else
                  throw std::system_error(GetLastError(), std::system_category());
          }())
    {
    }

    plugin(plugin &&other) noexcept : lib_(std::move(other.lib_)), obj_(std::exchange(other.obj_, nullptr))
    {
    }

    plugin &operator=(plugin &&other) noexcept
    {
        lib_ = std::move(other);
        obj_ = std::exchange(other.obj_, nullptr);
        return *this;
    }

    auto operator->() const noexcept
    {
        return obj_;
    }

    auto operator->() noexcept
    {
        return obj_;
    }
};

}