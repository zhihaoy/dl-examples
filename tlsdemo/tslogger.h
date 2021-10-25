#pragma once

namespace tslogger
{

class logger
{
  public:
    virtual ~logger() = default;
};

class singleton
{
  public:
    virtual auto get() -> logger & = 0;
};

}
