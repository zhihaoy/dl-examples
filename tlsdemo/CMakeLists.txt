find_package(Threads REQUIRED)

# application verifier doesn't flag leak in a debug runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

add_library(tslogger MODULE)
target_sources(tslogger 
    PUBLIC "tslogger.h"
    PRIVATE "tslogger.cpp"
)
set_target_properties(tslogger PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
)

add_executable(tlsdemo)
target_sources(tlsdemo PRIVATE
    "tlsdemo.cpp"
    "plugin.h"
    "plugin_traits.h"
    "plugin_traits_$<IF:$<PLATFORM_ID:Windows>,win32,posix>.cpp"
)
target_link_libraries(tlsdemo PRIVATE
    Threads::Threads
    ${CMAKE_DL_LIBS}
)
