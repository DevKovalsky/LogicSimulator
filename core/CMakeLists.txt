cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME core)

project(${PROJECT_NAME})

file(GLOB_RECURSE core_src src/*.cpp)
file(GLOB_RECURSE core_inc include/*.h)

add_library(${PROJECT_NAME}
        STATIC
        ${core_src}
        ${core_inc}
        )

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        utils
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include
        )
