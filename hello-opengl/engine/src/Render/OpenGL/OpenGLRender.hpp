#pragma once

#include "Render.hpp"
#include <memory>

namespace Engine {

class OpenGLRender : public Render {
  public:
    OpenGLRender();
    virtual ~OpenGLRender();
    virtual void setClearColor(float r, float g, float b, float a) override;
    virtual void color() override;
    virtual void drawLines(std::shared_ptr<Shader> shader,
                           std::shared_ptr<VertexArray> vertexArray) override;
    virtual void
    drawTriangles(std::shared_ptr<Shader> shader,
                  std::shared_ptr<VertexArray> vertexArray) override;
};

} // namespace Engine
