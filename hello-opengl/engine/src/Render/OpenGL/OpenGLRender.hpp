#pragma once

#include "Render.hpp"
#include "glad/glad.h"
#include <memory>

namespace Engine {

class OpenGLRender : public Render {
  public:
    OpenGLRender();
    virtual ~OpenGLRender();
    virtual void setViewport(uint16_t width, uint16_t height) override;
    virtual void setClearColor(float r, float g, float b, float a) override;
    virtual void clear() override;
    virtual void drawLines(std::shared_ptr<Shader> shader,
                           std::shared_ptr<VertexArray> vertexArray) override;
    virtual void
    drawTriangles(std::shared_ptr<Shader> shader,
                  std::shared_ptr<VertexArray> vertexArray) override;
    virtual void drawTexture(std::shared_ptr<Shader> shader,
                             std::shared_ptr<VertexArray> vertexArray,
                             std::shared_ptr<Texture> texture) override;
    virtual void drawTexture(std::shared_ptr<Shader> shader,
                             std::shared_ptr<VertexArray> vertexArray,
                             Texture *texture) override;
};

} // namespace Engine
