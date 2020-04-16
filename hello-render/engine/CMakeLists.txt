cmake_minimum_required(VERSION 3.13)

project(Engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_LIB ${CMAKE_CURRENT_SOURCE_DIR}/src)	

add_library(engine SHARED ${SOURCE_LIB})

set_target_properties(engine PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
target_include_directories(engine PUBLIC /usr/local/Cellar/sdl2/2.0.10/include)
target_link_libraries(engine PRIVATE ${SDL2_LIBRARIES})
