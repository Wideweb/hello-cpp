#include "OpenGLRender.hpp"

namespace Engine {

OpenGLRender::OpenGLRender() {}

OpenGLRender::~OpenGLRender() {}

void OpenGLRender::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void OpenGLRender::color() { glClear(GL_COLOR_BUFFER_BIT); }

void OpenGLRender::drawLines(std::shared_ptr<Shader> shader,
                             std::shared_ptr<VertexArray> vertexArray) {
    vertexArray->bind();
    glDrawElements(GL_LINES, vertexArray->getIndexBuffer()->getCount(),
                   GL_UNSIGNED_INT, nullptr);
}

void OpenGLRender::drawTriangles(std::shared_ptr<Shader> shader,
                                 std::shared_ptr<VertexArray> vertexArray) {
    shader->bind();
    vertexArray->bind();
    glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(),
                   GL_UNSIGNED_INT, nullptr);
}

} // namespace Engine
