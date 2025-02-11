cmake_minimum_required(VERSION 3.23)

set(project "lab_2_planets")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
    main.cpp
)

add_subdirectory(planet)

set(${project}_SOURCE_LIST
    ${${project}_SOURCES}
)

add_executable(${project}
    ${${project}_SOURCE_LIST}
)

target_link_libraries(${project} planet)

set_target_properties(${project} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
