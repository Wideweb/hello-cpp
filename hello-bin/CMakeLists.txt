cmake_minimum_required(VERSION 3.10)

project(HelloBin VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_EXE hello.cpp)	

add_executable(hello ${SOURCE_EXE})

target_link_libraries(hello PUBLIC helloLib)
