#include "Buffer.hpp"
#include "OpenGLBuffer.hpp"

namespace Engine {

VertexBuffer *VertexBuffer::create(const std::vector<float> &vertices) {
    return new OpenGLVertexBuffer(vertices);
}

IndexBuffer *IndexBuffer::create(const std::vector<uint32_t> &indexes) {
    return new OpenGLIndexBuffer(indexes);
}

} // namespace Engine
