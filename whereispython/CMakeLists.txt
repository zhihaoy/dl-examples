add_library(whereispython INTERFACE)
target_sources(whereispython INTERFACE "whereispython.h")
target_include_directories(whereispython
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_library(fullinstaller MODULE)
target_sources(fullinstaller
    PRIVATE "fullinstaller.cpp"
)

string(REPLACE "/EHsc" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

add_library(microsoftstore MODULE)
target_sources(microsoftstore
    PRIVATE "microsoftstore.cpp"
)
target_compile_options(microsoftstore PRIVATE "/clr")
