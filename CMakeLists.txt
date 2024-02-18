cmake_minimum_required(VERSION 3.27)
project(ftm)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

add_executable(ftm
        engine/main.cpp
        engine/display.cpp
        engine/display.h
        engine/triangle.h.cpp
        engine/triangle.h.h
        engine/vector.cpp
        engine/vector.h
        engine/mesh.cpp
        engine/mesh.h
        engine/face.cpp
        engine/face.h
)

target_link_libraries(ftm ${SDL2_LIBRARIES} GLEW::GLEW)
