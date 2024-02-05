cmake_minimum_required(VERSION 3.27)
project(ftm)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(ftm
        engine/main.cpp
        engine/display.cpp
        engine/display.h
)

target_link_libraries(ftm ${SDL2_LIBRARIES})
