#pragma once

#include <filesystem>

namespace tlsdemo
{

template <class Handle> struct plugin_traits
{
    static auto open(std::filesystem::path) -> Handle;
    static auto resolve(Handle) -> void *;
    static void close(Handle) noexcept;
};

}