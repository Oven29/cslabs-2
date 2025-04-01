cmake_minimum_required(VERSION 3.23)

set(project "set")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
)

set(${project}_HEADERS
    vector.hpp
    set.hpp
)

set(${project}_SOURCE_LIST
    ${${project}_SOURCES}
    ${${project}_HEADERS}
)

add_library(${project}
    STATIC
    ${${project}_SOURCE_LIST}
)

set_target_properties(${project} PROPERTIES LINKER_LANGUAGE CXX)
