cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME main)

project(${PROJECT_NAME})

file(GLOB_RECURSE main_src src/*.cpp)
file(GLOB_RECURSE main_inc include/*.h)

add_executable(${PROJECT_NAME}
        ${main_src}
        ${main_inc}
        )

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        core
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        include
        )