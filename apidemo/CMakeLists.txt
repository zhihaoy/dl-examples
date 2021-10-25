add_executable(apidemo)
target_sources(apidemo PRIVATE
    "apidemo_$<IF:$<PLATFORM_ID:Windows>,win32,posix>.cpp"
)
target_include_directories(apidemo 
    PRIVATE
    "$<TARGET_PROPERTY:repromath,INTERFACE_INCLUDE_DIRECTORIES>"
)
target_link_libraries(apidemo PRIVATE ${CMAKE_DL_LIBS})