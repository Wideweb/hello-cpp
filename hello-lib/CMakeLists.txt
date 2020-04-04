cmake_minimum_required(VERSION 3.13)

project(HelloLib VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_LIB hello.cpp)	

if(BUILD_SHARED_LIBS)
    message("Build hello-lib as shared")
    add_library(helloLib SHARED ${SOURCE_LIB})
else()
    message("Build hello-lib as static")
    add_library(helloLib STATIC ${SOURCE_LIB})
endif()

target_include_directories(helloLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
