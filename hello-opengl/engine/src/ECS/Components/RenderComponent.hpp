#pragma once

#include "Buffer.hpp"
#include "Entity.hpp"
#include "Math.hpp"
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
    std::string shader;

    RenderComponent(int width, int height, Vec3 color,
                    const std::string &shader);

  private:
    void init(std::vector<float> &vertices, std::vector<uint32_t> &indexes,
              const std::string &shader, int width, int height);
};

} // namespace Engine