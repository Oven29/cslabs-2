cmake_minimum_required(VERSION 3.23)

project("lab_8_STL")

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    main.cpp
    src/app.cpp
)

set(HEADERS
    src/app.h
)

set(SOURCE_LIST ${SOURCES} ${HEADERS})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_LIST})

# target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)

# Enable debug symbols if flag is set ENABLE_DEBUG (`cd build && cmake -ENABLE_DEBUG=True ..`)
if(ENABLE_DEBUG)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g)
endif()

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
