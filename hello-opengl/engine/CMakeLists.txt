cmake_minimum_required(VERSION 3.13)

project(Engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_LIB 
    vendor/glad/glad.c
    src/Core/Application.cpp
    src/Core/Window.cpp
    src/Core/Input.cpp
    src/Core/SDL/SDLWindow.cpp
    src/Core/SDL/SDLInput.cpp
    src/Core/Layer.cpp
    src/Core/Time.cpp
    src/Core/TextureManager.cpp
    src/Core/ShaderManager.cpp
    src/Core/File.cpp
    src/Core/Loader.cpp
    src/Animation/AnimationLoader.cpp
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
    src/ECS/EntitySerializer.cpp
    src/ECS/Systems/CameraSystem.cpp
    src/ECS/Systems/CollisionSystem.cpp
    src/ECS/Systems/MoveSystem.cpp
    src/ECS/Systems/PhysicsSystem.cpp
    src/ECS/Systems/RenderSystem.cpp
    src/ECS/Systems/MorphingSystem.cpp
    src/ECS/Systems/AnimationSystem.cpp
    src/ECS/Systems/TextureSystem.cpp
    src/ECS/Systems/LightSystem.cpp
    src/ECS/Systems/SpotLightSystem.cpp
    src/ECS/Systems/SteeringSystem.cpp
    src/ECS/Systems/AISystem.cpp
    src/ECS/Systems/AttackSystem.cpp
    src/ECS/Systems/EmitterSystem.cpp
    src/ECS/Systems/GroundCollisionSystem.cpp
    src/Collision/CollisionDetection.cpp
    src/Collision/BroadPhaseAlgorithm.cpp
    src/Collision/NarrowPhaseAlgorithm.cpp
    src/Collision/AABBOverlap.cpp
    src/ImGui/ImGuiLayer.cpp
    src/Sound/SoundMixer.cpp
    src/Sound/SDL/SDLSoundBuffer.cpp
    src/Sound/SDL/SDLSoundMixer.cpp
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
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Collision
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Collision/Shapes
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Animation
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/ImGui
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Sound
                                         ${CMAKE_CURRENT_SOURCE_DIR}/src/Sound/SDL
                                         ${CMAKE_CURRENT_SOURCE_DIR}/vendor)


find_package(SDL2 REQUIRED)
target_include_directories(engine PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(engine PRIVATE ${SDL2_LIBRARIES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
target_link_libraries(engine PRIVATE imgui)