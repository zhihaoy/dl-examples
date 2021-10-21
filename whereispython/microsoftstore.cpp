#include "whereispython.h"

#pragma comment(linker, "/export:factory=?instance@@3Vmicrosoftstore_factory@whereispython@@A")

namespace whereispython
{

class microsoftstore : public installation
{
  public:
    explicit microsoftstore(wchar_t const *version)
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

class microsoftstore_factory : public factory
{
  public:
    virtual auto operator[](wchar_t const *version) -> std::unique_ptr<installation>
    {
        return std::make_unique<microsoftstore>(version);
    }
};

}

whereispython::microsoftstore_factory instance;
