cmake_minimum_required(VERSION 3.17)

project(HelloSdl VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_EXE main.cpp)	

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(hello ${SOURCE_EXE})

if(BUILD_SHARED_LIBS)
    target_link_libraries(hello SDL2::SDL2)
else()
    target_link_libraries(hello SDL2::SDL2-static)
endif()
