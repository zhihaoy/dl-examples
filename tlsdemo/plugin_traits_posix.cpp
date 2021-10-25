#include "plugin_traits.h"

#include <dlfcn.h>

namespace tlsdemo
{

template <> auto plugin_traits<void *>::open(std::filesystem::path filename) -> void *
{
    if (auto lib = ::dlopen(filename.c_str(), RTLD_LOCAL | RTLD_NOW))
        return lib;
    else
        throw std::runtime_error{::dlerror()};
}

template <> auto plugin_traits<void *>::resolve(void *lib) -> void *
{
    if (auto pinst = ::dlsym(lib, "instance"))
        return pinst;
    else
        throw std::runtime_error{::dlerror()};
}

template <> void plugin_traits<void *>::close(void *lib) noexcept
{
    ::dlclose(lib);
}

}
