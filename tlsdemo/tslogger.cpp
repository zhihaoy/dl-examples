#include "tslogger.h"

#include <memory>

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
