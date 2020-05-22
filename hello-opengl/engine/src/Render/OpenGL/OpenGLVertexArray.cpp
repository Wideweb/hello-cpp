#include "OpenGLVertexArray.hpp"
#include "Debug.hpp"

namespace Engine {

GLenum getBaseType(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:
        return GL_FLOAT;
    case ShaderDataType::Float2:
        return GL_FLOAT;
    case ShaderDataType::Float3:
        return GL_FLOAT;
    case ShaderDataType::Float4:
        return GL_FLOAT;
    default:
        return GL_FLOAT;
    }
}

OpenGLVertexArray::OpenGLVertexArray() { glGenVertexArrays(1, &m_RendererID); }

OpenGLVertexArray::~OpenGLVertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::bind() {
    GL_CHECK();
    glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::unbind() {
    glBindVertexArray(0);
    GL_CHECK();
}

void OpenGLVertexArray::addVertexBuffer(
    const std::shared_ptr<VertexBuffer> &vertexBuffer) {
    glBindVertexArray(m_RendererID);
    GL_CHECK();
    vertexBuffer->bind();

    const auto &layout = vertexBuffer->getLayout();
    uint32_t index = 0;
    for (const auto &element : layout) {
        glEnableVertexAttribArray(index);
        GL_CHECK();
        glVertexAttribPointer(index, element.getElementCount(),
                              getBaseType(element.type), GL_FALSE,
                              layout.getStride(),
                              reinterpret_cast<void *>(element.offset));
        GL_CHECK();
        index++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(
    const std::shared_ptr<IndexBuffer> &indexBuffer) {
    glBindVertexArray(m_RendererID);
    GL_CHECK();
    indexBuffer->bind();
    m_IndexBuffer = indexBuffer;
}

const std::shared_ptr<IndexBuffer> &OpenGLVertexArray::getIndexBuffer() const {
    return m_IndexBuffer;
}

}; // namespace Engine
