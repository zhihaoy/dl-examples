include(GenerateExportHeader)

add_library(repromath SHARED)
target_sources(repromath
    PRIVATE "repromath.cpp"
    PUBLIC "repromath.h"
           "${CMAKE_CURRENT_BINARY_DIR}/repromath_export.h"
)
set_target_properties(repromath PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_include_directories(repromath
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
generate_export_header(repromath)
