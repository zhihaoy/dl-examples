add_executable(apidemo)
target_sources(apidemo PRIVATE
    "$<$<PLATFORM_ID:Windows>:apidemo_win32.cpp>"
    "$<$<NOT:$<PLATFORM_ID:Windows>>:apidemo_posix.cpp>"
)
target_include_directories(apidemo 
    PRIVATE
    "$<TARGET_PROPERTY:repromath,INTERFACE_INCLUDE_DIRECTORIES>"
)
target_link_libraries(apidemo PRIVATE ${CMAKE_DL_LIBS})