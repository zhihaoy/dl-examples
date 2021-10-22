#include "openplugins.h"

#include <Windows.h>
#include <fileapi.h>

template <class T> inline auto transfer_find(T *key)
{
    struct find_file_deleter
    {
        void operator()(T *key) const noexcept
        {
            ::FindClose(key);
        }
    };
    return std::unique_ptr<T, find_file_deleter>(key);
}

template <class Fn> static void for_each_dll_under(std::filesystem::path const &dir, Fn fn)
{
    WIN32_FIND_DATAW data[1];
    if (auto handle = ::FindFirstFileW((dir / "*.dll").c_str(), data); handle != INVALID_HANDLE_VALUE)
    {
        auto files = transfer_find(handle);
        do
        {
            fn(dir / data->cFileName);
        } while (::FindNextFileW(files.get(), data));
    }

    if (auto ec = GetLastError(); ec != ERROR_NO_MORE_FILES)
        throw std::system_error(ec, std::system_category());
}

auto plugindemo::openplugins(std::filesystem::path dir) -> std::vector<plugin<whereispython::factory>>
{
    std::vector<plugin<whereispython::factory>> ls;
    for_each_dll_under(dir, [&](std::filesystem::path const &dll) { ls.emplace_back(dll); });
    return ls;
}