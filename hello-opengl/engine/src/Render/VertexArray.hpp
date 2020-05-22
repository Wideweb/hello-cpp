#pragma once

#include "Buffer.hpp"
#include <memory>

namespace Engine {

class VertexArray {
  public:
    virtual ~VertexArray() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void
    addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;

    virtual void
    setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) = 0;

    virtual const std::shared_ptr<IndexBuffer> &getIndexBuffer() const = 0;

    static VertexArray *create();
};

} // namespace Engine
