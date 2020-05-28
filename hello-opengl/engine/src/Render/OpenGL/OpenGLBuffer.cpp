#include "OpenGLBuffer.hpp"
#include "Debug.hpp"
#include <cassert>

namespace Engine {

/////////////////////////////////////////////////////////////////////////////
// VertexBuffer /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<float> &vertices)
    : m_Vertices(vertices), m_Size(vertices.size() * sizeof(float)) {

    glGenBuffers(1, &m_RendererID);
    GL_CHECK();
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &m_RendererID); }

void OpenGLVertexBuffer::setVertices(const std::vector<float> &vertices) {
    m_Vertices = vertices;
}

void OpenGLVertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    GL_CHECK();
    glBufferData(GL_ARRAY_BUFFER, m_Size, m_Vertices.data(), GL_STATIC_DRAW);
    GL_CHECK();
}

void OpenGLVertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GL_CHECK();
}

void OpenGLVertexBuffer::setLayout(BufferLayout &layout) { m_Layout = layout; }

////////////////////////////////////////////////////////////////////////////
// IndexBuffer /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<uint32_t> &indexes)
    : m_Indexes(indexes), m_Count(indexes.size()) {
    glGenBuffers(1, &m_RendererID);
    GL_CHECK();
}
OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &m_RendererID); }

void OpenGLIndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    GL_CHECK();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indexes.size() * sizeof(uint32_t),
                 m_Indexes.data(), GL_STATIC_DRAW);
    GL_CHECK();
}

void OpenGLIndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GL_CHECK();
}

} // namespace Engine
