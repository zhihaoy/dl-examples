#include "whereispython.h"

#include <msclr/marshal_cppstd.h>
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
    std::filesystem::path install_location_;

  public:
    explicit microsoftstore(char const *version)
    {
        using namespace msclr::interop;
        using namespace std::string_literals;

        auto shell = PowerShell::Create()
                         ->AddCommand("Get-AppxPackage")
                         ->AddParameter("-Name", gcnew String("*Python."s.append(version).data()));
        for each (auto python in shell->Invoke())
        {
            auto value = python->Members["InstallLocation"]->Value->ToString();
            install_location_ = marshal_as<std::wstring>(value);
            break;
        }
        if (install_location_.empty())
            throw std::runtime_error{"No such Python installation"};
    }

    auto executable() -> std::filesystem::path override
    {
        return install_location_ / L"python.exe";
    }

    auto windowed_executable() -> std::filesystem::path override
    {
        return install_location_ / L"pythonw.exe";
    }
};

class microsoftstore_factory : public factory
{
  public:
    virtual auto lookup(char const *version) -> std::unique_ptr<installation>
    {
        try
        {
            return std::make_unique<microsoftstore>(version);
        }
        catch (std::exception &)
        {
            return nullptr;
        }
    }
};

}

whereispython::microsoftstore_factory instance;
