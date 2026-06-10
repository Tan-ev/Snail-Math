cmake_minimum_required(VERSION 3.16)

project(SnailMath VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

add_library(SM SHARED
    source/primary.cpp
)

target_include_directories(SM PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(SM PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wno-c11-extensions
)