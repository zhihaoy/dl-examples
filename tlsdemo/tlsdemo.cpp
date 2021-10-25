#include "plugin.h"
#include "tslogger.h"

#include <chrono>
#include <thread>

#if defined(_WIN32)
static wchar_t const libname[] = L"tslogger.dll";
#else
static char const libname[] = "libtslogger.so";
#endif

using namespace std::chrono_literals;

int main()
{
    auto inst = tlsdemo::plugin<tslogger::singleton>(std::filesystem::current_path() / libname);

    std::thread th[] = {std::thread([&] {
                            inst->get();
                            std::this_thread::sleep_for(1s);
                        }),
                        std::thread([&] {
                            std::this_thread::sleep_for(200ms);
                            inst->get();
                            inst.unload();
                        })};

    for (auto &thr : th)
        thr.join();
}