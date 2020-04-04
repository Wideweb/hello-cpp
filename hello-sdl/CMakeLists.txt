cmake_minimum_required(VERSION 3.13)

project(HelloSdl VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_EXE main.cpp)	

add_executable(hello ${SOURCE_EXE})

if(BUILD_SHARED_LIBS)
    target_link_libraries(hello PRIVATE SDL2::SDL2)
else()
    target_link_libraries(hello PRIVATE SDL2::SDL2-static SDL2::SDL2main)
endif()
