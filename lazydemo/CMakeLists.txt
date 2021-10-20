add_executable(lazydemo)

# Workaround for CMake<3.20
if(NOT WIN32)
    set_source_files_properties(
        "${CMAKE_CURRENT_BINARY_DIR}/../lazyrepromath/liblazyrepromath.so.tramp.S"
        "${CMAKE_CURRENT_BINARY_DIR}/../lazyrepromath/liblazyrepromath.so.init.c"
        PROPERTIES GENERATED YES)
endif()

target_sources(lazydemo PRIVATE "lazydemo.cpp")
target_link_libraries(lazydemo PRIVATE lazyrepromath)
