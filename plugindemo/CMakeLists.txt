add_executable(list-python-by-version)
target_sources(list-python-by-version PRIVATE
    "source.cpp"
    "plugin.h"
    "openplugins.h"
    "openplugins.cpp"
)
target_link_libraries(list-python-by-version PRIVATE whereispython)