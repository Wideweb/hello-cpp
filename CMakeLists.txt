cmake_minimum_required(VERSION 3.10)

project(Hello VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_subdirectory(hello-lib)
add_subdirectory(hello-bin)
