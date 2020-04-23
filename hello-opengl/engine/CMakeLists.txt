cmake_minimum_required(VERSION 3.13)

project(Engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_LIB 
    external/glad/glad.c
    src/Core/Application.cpp
    src/Core/Window.cpp
    src/Core/SDLWindow.cpp
    src/Render/Buffer.cpp
    src/Render/Render.cpp
    src/Render/Shader.cpp
    src/Render/VertexArray.cpp
    src/Render/OpenGL/OpenGLBuffer.cpp
    src/Render/OpenGL/OpenGLRender.cpp
    src/Render/OpenGL/OpenGLShader.cpp
    src/Render/OpenGL/OpenGLVertexArray.cpp
)	

add_library(engine SHARED ${SOURCE_LIB})

set_target_properties(engine PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Core
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Render
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Render/OpenGL
                                         ${CMAKE_CURRENT_SOURCE_DIR}/external)

find_package(SDL2 REQUIRED)
target_include_directories(engine PUBLIC /usr/local/Cellar/sdl2/2.0.12_1/include)
target_link_libraries(engine PRIVATE SDL2::SDL2)
