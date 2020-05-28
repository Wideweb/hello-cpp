#pragma once

#include "Shader.hpp"
#include "glad/glad.h"
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

    virtual void setInt(const std::string &name, int value) override;
    virtual void setFloat(const std::string &name, float value) override;
    virtual void setFloat2(const std::string &name, float value1,
                           float value2) override;
    virtual void setFloat3(const std::string &name, float value, float value2,
                           float value3) override;
    virtual void setMatrix4(const std::string &name,
                            const std::vector<float> &matrix) override;
    virtual void setMatrix2x3(const std::string &name,
                              const std::vector<float> &matrix) override;
    virtual void setMatrix2(const std::string &name,
                            const std::vector<float> &matrix) override;

  private:
    void compile(const std::string &vertexSrc, const std::string &fragmentSrc);
    GLuint compileShader(GLenum type, const std::string &source);
};

} // namespace Engine