#include "plugin_traits.h"

#include <Windows.h>
#include <libloaderapi.h>

namespace tlsdemo
{

template <> auto plugin_traits<HMODULE>::open(std::filesystem::path filename) -> HMODULE
{
    if (auto lib = ::LoadLibraryExW(filename.c_str(), nullptr,
                                    LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR))
        return lib;
    else
        throw std::system_error(GetLastError(), std::system_category());
}

template <> auto plugin_traits<HMODULE>::resolve(HMODULE lib) -> void *
{
    if (auto pinst = ::GetProcAddress(lib, "instance"))
        return (void *)pinst;
    else
        throw std::system_error(GetLastError(), std::system_category());
}

template <> void plugin_traits<HMODULE>::close(HMODULE lib) noexcept
{
    ::FreeLibrary(lib);
}

}
