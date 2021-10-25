#include "tslogger.h"

#include <iostream>
#include <memory>
#include <thread>

#if defined(_MSC_VER)
#pragma comment(linker, "/export:instance=?instance@@3Vmemory_logger_singleton@tslogger@@A")
#define EXPORT_UNDNAME
#else
#define EXPORT_UNDNAME __attribute__((visibility("default")))
#endif

namespace tslogger
{

class memory_logger : public logger
{
    std::unique_ptr<char[]> buf_ = std::make_unique<char[]>(1024);

  public:
    memory_logger()
    {
        std::cout << " + thread (" << std::this_thread::get_id() << ") attached\n";
    }

    ~memory_logger()
    {
        std::cout << " - thread (" << std::this_thread::get_id() << ") detached\n";
    }
};

class memory_logger_singleton : public singleton
{
  public:
    virtual auto get() -> logger & override
    {
        thread_local memory_logger inst;
        return inst;
    }
};

}

EXPORT_UNDNAME tslogger::memory_logger_singleton instance;
