#include "whereispython.h"

#pragma comment(linker, "/export:factory=?instance@@3Vfullinstaller_factory@whereispython@@A")

namespace whereispython
{

class fullinstaller : public installation
{
  public:
    explicit fullinstaller(wchar_t const *version)
    {
    }

    auto executable() -> std::filesystem::path override
    {
        return "";
    }

    auto windowed_executable() -> std::filesystem::path override
    {
        return "";
    }
};

class fullinstaller_factory : public factory
{
  public:
    virtual auto operator[](wchar_t const *version) -> std::unique_ptr<installation>
    {
        return std::make_unique<fullinstaller>(version);
    }
};

}

whereispython::fullinstaller_factory instance;