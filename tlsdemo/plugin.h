#pragma once

#include "plugin_traits.h"

#include <memory>

struct HINSTANCE__;

namespace tlsdemo
{

template <class Factory> class plugin
{
#if defined(_WIN32)
    using incomplete_type = HINSTANCE__;
#else
    using incomplete_type = void;
#endif
    using traits = plugin_traits<incomplete_type *>;

    struct library_deleter
    {
        void operator()(incomplete_type *lib) const noexcept
        {
            traits::close(lib);
        }
    };

    std::unique_ptr<incomplete_type, library_deleter> lib_;
    Factory *obj_;

  public:
    explicit plugin(std::filesystem::path const &filename)
        : lib_(traits::open(filename)), obj_((Factory *)traits::resolve(lib_.get()))
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

    void unload()
    {
        lib_ = nullptr;
        obj_ = nullptr;
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