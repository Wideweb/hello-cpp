cmake_minimum_required(VERSION 3.17)

project(Hello VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# add_subdirectory(hello-lib)
# add_subdirectory(hello-bin)
add_subdirectory(hello-sdl)
