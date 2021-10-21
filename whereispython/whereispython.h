#pragma once

#include <filesystem>
#include <memory>

namespace whereispython
{

class installation
{
  public:
    virtual auto executable() -> std::filesystem::path = 0;
    virtual auto windowed_executable() -> std::filesystem::path = 0;
    virtual ~installation() = default;
};

class factory
{
  public:
    virtual auto lookup(char const *ver) -> std::unique_ptr<installation> = 0;
};

}