#include "whereispython.h"

#include <vcclr.h>
// clang-format off
#using <mscorlib.dll>
#using <System.dll>
#using <System.Management.Automation.dll>
// clang-format on

using namespace System;
using namespace System::Management::Automation;

#pragma comment(linker, "/export:instance=?instance@@3Vmicrosoftstore_factory@whereispython@@A")

namespace whereispython
{

class microsoftstore : public installation
{
  public:
    explicit microsoftstore(char const *version)
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
    virtual auto lookup(char const *version) -> std::unique_ptr<installation>
    {
        return std::make_unique<microsoftstore>(version);
    }
};

}

whereispython::microsoftstore_factory instance;
