#include "openplugins.h"

template <class Fn> static void for_each_dll_under(std::filesystem::path const &dir, Fn fn)
{
    fn(dir / "fullinstaller.dll");
    fn(dir / "microsoftstore.dll");
}

auto plugindemo::openplugins(std::filesystem::path dir) -> std::vector<plugin<whereispython::factory>>
{
    std::vector<plugin<whereispython::factory>> ls;
    for_each_dll_under(dir, [&](std::filesystem::path const &dll) { ls.emplace_back(dll); });
    return ls;
}