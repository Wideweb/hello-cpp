#pragma once

#include "VertexArray.hpp"
#include "glad/glad.h"

namespace Engine {

class OpenGLVertexArray : public VertexArray {
  private:
    uint32_t m_RendererID;
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;

  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void bind() override;
    virtual void unbind() override;

    virtual void
    addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;

    virtual void
    setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

    virtual const std::shared_ptr<IndexBuffer> &getIndexBuffer() const override;
};

} // namespace Engine
