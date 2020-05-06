cmake_minimum_required(VERSION 3.13)

project(Engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_LIB 
    external/glad/glad.c
    src/Core/Application.cpp
    src/Core/Window.cpp
    src/Core/Input.cpp
    src/Core/SDL/SDLWindow.cpp
    src/Core/SDL/SDLInput.cpp
    src/Core/Layer.cpp
    src/Core/Time.cpp
    src/Core/TextureManager.cpp
    src/Render/Buffer.cpp
    src/Render/Render.cpp
    src/Render/Shader.cpp
    src/Render/VertexArray.cpp
    src/Render/Camera.cpp
    src/Render/Texture.cpp
    src/Render/OpenGL/OpenGLBuffer.cpp
    src/Render/OpenGL/OpenGLRender.cpp
    src/Render/OpenGL/OpenGLShader.cpp
    src/Render/OpenGL/OpenGLVertexArray.cpp
    src/Render/OpenGL/OpenGLTexture.cpp
    src/ECS/Components/RenderComponent.cpp
    src/ECS/Components/MorphingComponent.cpp
    src/ECS/Components/TextureComponent.cpp
    src/ECS/SystemStack.cpp
    src/ECS/Systems/CameraSystem.cpp
    src/ECS/Systems/CollisionSystem.cpp
    src/ECS/Systems/ControlSystem.cpp
    src/ECS/Systems/MoveSystem.cpp
    src/ECS/Systems/PhysicsSystem.cpp
    src/ECS/Systems/RenderSystem.cpp
    src/ECS/Systems/MorphingSystem.cpp
    src/ECS/Systems/TextureSystem.cpp
    src/ECS/Systems/AISystem.cpp
    src/Math.cpp
)	

add_library(engine SHARED ${SOURCE_LIB})

set_target_properties(engine PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Core
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/SDL
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Render
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Render/OpenGL
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Events
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Systems
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/AI/BehaviourTree
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/AI/BehaviourTree/Tasks
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/AI/BehaviourTree/TaskDecorators
                                         ${CMAKE_CURRENT_SOURCE_DIR}/external)

find_package(SDL2 REQUIRED)
target_include_directories(engine PUBLIC /usr/local/Cellar/sdl2/2.0.12_1/include)
target_link_libraries(engine PRIVATE SDL2::SDL2)
