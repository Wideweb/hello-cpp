#include "OpenGLRender.hpp"
#include "Debug.hpp"

namespace Engine {

OpenGLRender::OpenGLRender() {}

OpenGLRender::~OpenGLRender() {}

void OpenGLRender::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    GL_CHECK();
}

void OpenGLRender::setViewport(uint16_t width, uint16_t height) {
    glViewport(0, 0, width, height);
}

void OpenGLRender::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
    GL_CHECK();
}

void OpenGLRender::drawLines(std::shared_ptr<Shader> shader,
                             std::shared_ptr<VertexArray> vertexArray) {
    shader->bind();
    vertexArray->bind();
    glDrawElements(GL_LINES, vertexArray->getIndexBuffer()->getCount(),
                   GL_UNSIGNED_INT, nullptr);
    GL_CHECK();
}

void OpenGLRender::drawTriangles(std::shared_ptr<Shader> shader,
                                 std::shared_ptr<VertexArray> vertexArray) {
    shader->bind();
    vertexArray->bind();
    glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(),
                   GL_UNSIGNED_INT, nullptr);
    GL_CHECK();
}

} // namespace Engine
