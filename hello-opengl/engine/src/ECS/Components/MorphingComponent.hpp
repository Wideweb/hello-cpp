#pragma once

#include "Buffer.hpp"
#include "Entity.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace Engine {

class MorphingComponent : public Component {
  public:
    int width;
    int height;

    std::shared_ptr<Engine::VertexArray> vertexArray;
    std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
    std::shared_ptr<Engine::IndexBuffer> indexBuffer;
    std::shared_ptr<Engine::Shader> shader;

    MorphingComponent(std::vector<float> &from, std::vector<float> &to,
                      std::vector<uint32_t> &indexes,
                      std::shared_ptr<Engine::Shader> shader, int width,
                      int height);
};

} // namespace Engine