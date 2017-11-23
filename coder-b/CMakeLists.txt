cmake_minimum_required(VERSION 3.8)
project(points)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vector3D.cpp Vector3D.h Plane.cpp Plane.h)
add_executable(points ${SOURCE_FILES})