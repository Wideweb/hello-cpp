#include "OpenGLVertexArray.hpp"

namespace Engine {

OpenGLVertexArray::OpenGLVertexArray() { glGenVertexArrays(1, &m_RendererID); }

OpenGLVertexArray::~OpenGLVertexArray() {}

void OpenGLVertexArray::bind() { glBindVertexArray(m_RendererID); }
void OpenGLVertexArray::unbind() { glBindVertexArray(0); }

void OpenGLVertexArray::addVertexBuffer(
    const std::shared_ptr<VertexBuffer> &vertexBuffer) {
    glBindVertexArray(m_RendererID);
    vertexBuffer->bind();

    const auto &layout = vertexBuffer->getLayout();
    uint32_t index = 0;
    for (const auto &element : layout) {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            index, element.getElementCount(), element.getBaseType(), GL_FALSE,
            layout.getStride(), reinterpret_cast<void *>(element.offset));
        index++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(
    const std::shared_ptr<IndexBuffer> &indexBuffer) {
    glBindVertexArray(m_RendererID);
    indexBuffer->bind();
    m_IndexBuffer = indexBuffer;
}

const std::shared_ptr<IndexBuffer> &OpenGLVertexArray::getIndexBuffer() const {
    return m_IndexBuffer;
}

}; // namespace Engine
