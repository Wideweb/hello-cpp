#pragma once

#include "Shader.hpp"
#include "VertexArray.hpp"
#include <memory>

namespace Engine {

class Render {
  public:
    virtual ~Render() = default;
    virtual void setClearColor(float r, float g, float b, float a) = 0;
    virtual void clear() = 0;
    virtual void drawLines(std::shared_ptr<Shader> shader,
                           std::shared_ptr<VertexArray> vertexArray) = 0;
    virtual void drawTriangles(std::shared_ptr<Shader> shader,
                               std::shared_ptr<VertexArray> vertexArray) = 0;

    static Render *create();
};

} // namespace Engine
