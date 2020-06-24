#pragma once

#include "Buffer.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace Engine {

class RenderComponent : public Component {
  private:
    Vec3 m_Color;

  public:
    int width;
    int height;

    std::shared_ptr<Engine::VertexArray> vertexArray;
    std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
    std::shared_ptr<Engine::IndexBuffer> indexBuffer;

    RenderComponent(int width, int height, Vec3 color);

    virtual void serialize(std::ostringstream &out) override {
        out << "render ";
        out << width << " ";
        out << height << " ";
        out << m_Color;
        out << std::endl;
    }

  private:
    void init(std::vector<float> &vertices, std::vector<uint32_t> &indexes,
              int width, int height);
};

} // namespace Engine