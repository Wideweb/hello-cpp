#pragma once

#include "Buffer.hpp"
#include "Entity.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace Engine {

class RenderComponent : public Component {
  public:
    int width;
    int height;

    std::shared_ptr<Engine::VertexArray> vertexArray;
    std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
    std::shared_ptr<Engine::IndexBuffer> indexBuffer;
    std::shared_ptr<Engine::Shader> shader;

    RenderComponent(std::vector<float> &vertices,
                    std::vector<uint32_t> &indexes,
                    std::shared_ptr<Engine::Shader> shader, int width,
                    int height);
};

} // namespace Engine