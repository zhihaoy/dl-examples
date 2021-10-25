#include "plugin.h"
#include "tslogger.h"

#if defined(_WIN32)
static wchar_t const libname[] = L"tslogger.dll";
#else
static char const libname[] = "libtslogger.so";
#endif

int main()
{
    auto inst = tlsdemo::plugin<tslogger::singleton>(std::filesystem::current_path() / libname);
    auto p = inst->get();
}