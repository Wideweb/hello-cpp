#pragma once

#include "../external/glad/glad.h"
#include "Shader.hpp"
#include <string>

namespace Engine {

class OpenGLShader : public Shader {
  private:
    GLuint m_Program;

  public:
    OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
    virtual ~OpenGLShader();

    virtual void bind() override;
    virtual void unbind() override;

  private:
    void compile(const std::string &vertexSrc, const std::string &fragmentSrc);
    GLuint compileShader(GLenum type, const std::string &source);
};

} // namespace Engine