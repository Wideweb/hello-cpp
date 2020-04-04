cmake_minimum_required(VERSION 3.13)

project(HelloSdl VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_EXE main.cpp)	

add_executable(hello ${SOURCE_EXE})

if(BUILD_SHARED_LIBS)
    add_external(TARGET hello SHARED LIB SDL2::SDL2)
else()
    add_external(TARGET hello STATIC LIB SDL2::SDL2-static)
    add_external(TARGET hello STATIC LIB SDL2::SDL2main)
endif()
