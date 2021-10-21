#include "whereispython.h"

#include <Windows.h>
#include <winreg.h>

#include <cstdio>
#include <stdexcept>
#include <string>
#include <system_error>

#pragma comment(linker, "/export:instance=?instance@@3Vfullinstaller_factory@whereispython@@A")

namespace whereispython
{

template <class T> inline auto transfer_registry_key(T *key)
{
    struct hkey_deleter
    {
        void operator()(T *key) const noexcept
        {
            ::RegCloseKey(key);
        }
    };
    return std::unique_ptr<T, hkey_deleter>(key);
}

class fullinstaller : public installation
{
    decltype(transfer_registry_key(HKEY())) hkey_;

  public:
    explicit fullinstaller(char const *version)
        : hkey_([=] {
              wchar_t key_name[48];
              if (swprintf_s(key_name, LR"(SOFTWARE\Python\PythonCore\%S\InstallPath)", version) == -1)
                  throw std::invalid_argument("Python version");

              return transfer_registry_key(open_registry_key(key_name));
          }())
    {
    }

    auto executable() -> std::filesystem::path override
    {
        return string_value(L"ExecutablePath");
    }

    auto windowed_executable() -> std::filesystem::path override
    {
        return string_value(L"WindowedExecutablePath");
    }

  private:
    auto string_value(wchar_t const *name) -> std::wstring
    {
        auto buf = string_value_buffer_for(name);
        auto len = static_cast<DWORD>(buf.size() * sizeof(wchar_t));
        if (auto ec = ::RegGetValueW(hkey_.get(), nullptr, name, RRF_RT_REG_SZ, nullptr, buf.data(), &len);
            ec != ERROR_SUCCESS)
            throw std::system_error(ec, std::system_category());
        buf.resize(len / sizeof(wchar_t) - 1);
        return buf;
    }

    auto string_value_buffer_for(wchar_t const *name) -> std::wstring
    {
        DWORD len;
        if (auto ec = ::RegQueryValueExW(hkey_.get(), name, nullptr, nullptr, nullptr, &len); ec != ERROR_SUCCESS)
            throw std::system_error(ec, std::system_category());
        return std::wstring(len / sizeof(wchar_t), L'\0');
    }

    static auto open_registry_key(const wchar_t *key_name) -> HKEY
    {
        HKEY key;
        if (auto ec = ::RegOpenKeyExW(HKEY_LOCAL_MACHINE, key_name, 0, KEY_QUERY_VALUE, &key); ec != ERROR_SUCCESS)
            throw std::system_error(ec, std::system_category());
        return key;
    }
};

class fullinstaller_factory : public factory
{
  public:
    virtual auto lookup(char const *version) -> std::unique_ptr<installation>
    {
        try
        {
            return std::make_unique<fullinstaller>(version);
        }
        catch (std::exception &)
        {
            return nullptr;
        }
    }
};

}

whereispython::fullinstaller_factory instance;
