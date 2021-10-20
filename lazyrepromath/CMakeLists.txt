include(GenerateExportHeader)

add_library(lazyrepromath_hidden SHARED)
target_sources(lazyrepromath_hidden
    PRIVATE "$<TARGET_PROPERTY:repromath,SOURCE_DIR>/repromath.cpp"
    PUBLIC "$<TARGET_PROPERTY:repromath,SOURCE_DIR>/repromath.h"
)
set_target_properties(lazyrepromath_hidden PROPERTIES
    OUTPUT_NAME lazyrepromath
    CXX_VISIBILITY_PRESET hidden)
target_include_directories(lazyrepromath_hidden
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    INTERFACE $<BUILD_INTERFACE:$<TARGET_PROPERTY:repromath,SOURCE_DIR>>
)
generate_export_header(lazyrepromath_hidden BASE_NAME "repromath")

if(MSVC OR "${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
    add_library(lazyrepromath ALIAS lazyrepromath_hidden)
    target_link_libraries(lazyrepromath_hidden INTERFACE delayimp)
    target_link_options(lazyrepromath_hidden INTERFACE "/DELAYLOAD:lazyrepromath.dll")
elseif(NOT WIN32)
    find_package(Python COMPONENTS Interpreter)
    add_custom_command(
        TARGET lazyrepromath_hidden
        POST_BUILD
        COMMAND Python::Interpreter
                "${CMAKE_CURRENT_SOURCE_DIR}/implib/implib-gen.py"
                "--library-load-name" "./liblazyrepromath.so"
                $<TARGET_FILE:lazyrepromath_hidden>
        BYPRODUCTS "liblazyrepromath.so.tramp.S"
                   "liblazyrepromath.so.init.c"
    )
    add_library(lazyrepromath INTERFACE)
    target_sources(lazyrepromath
        INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/liblazyrepromath.so.tramp.S"
                  "${CMAKE_CURRENT_BINARY_DIR}/liblazyrepromath.so.init.c"
    )
    target_include_directories(lazyrepromath
        INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        INTERFACE $<BUILD_INTERFACE:$<TARGET_PROPERTY:repromath,SOURCE_DIR>>
    )
    target_link_libraries(lazyrepromath INTERFACE ${CMAKE_DL_LIBS})
endif()