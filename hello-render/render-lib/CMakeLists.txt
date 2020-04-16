cmake_minimum_required(VERSION 3.13)

project(RenderLib VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_LIB ${CMAKE_CURRENT_SOURCE_DIR}/src)	

add_library(renderLib SHARED ${SOURCE_LIB})

set_target_properties(renderLib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(renderLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
target_include_directories(renderLib PUBLIC /usr/local/Cellar/sdl2/2.0.10/include)
target_link_libraries(renderLib PRIVATE ${SDL2_LIBRARIES})
