cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME utils)

project(${PROJECT_NAME})

file(GLOB_RECURSE utils_src src/*.cpp)
file(GLOB_RECURSE utils_inc include/*.h)

add_library(${PROJECT_NAME}
        ${utils_src}
        ${utils_inc}
        )

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include
        )
