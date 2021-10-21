#pragma once

#include "plugin.h"
#include "whereispython.h"

#include <filesystem>
#include <vector>

namespace plugindemo
{

auto openplugins(std::filesystem::path dir) -> std::vector<plugin<whereispython::factory>>;

}