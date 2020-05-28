#include "OpenGLShader.hpp"
#include "Debug.hpp"
#include <iostream>
#include <vector>

namespace Engine {

OpenGLShader::OpenGLShader(const std::string &vertexSrc,
                           const std::string &fragmentSrc) {
    compile(vertexSrc, fragmentSrc);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(m_Program); };

void OpenGLShader::bind() {
    glUseProgram(m_Program);
    GL_CHECK();
}

void OpenGLShader::unbind() {
    glUseProgram(0);
    GL_CHECK();
}

void OpenGLShader::compile(const std::string &vertexSrc,
                           const std::string &fragmentSrc) {

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    if (vertexShader == 0) {
        return;
    }

    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);
    if (fragmentShader == 0) {
        return;
    }

    GLuint programId = glCreateProgram();
    GL_CHECK();
    if (programId == 0) {
        std::cerr << "failed to create gl program";
        return;
    }

    glAttachShader(programId, vertexShader);
    GL_CHECK();
    glAttachShader(programId, fragmentShader);
    GL_CHECK();

    glLinkProgram(programId);
    GL_CHECK();

    GLint linked_status = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &linked_status);
    GL_CHECK();
    if (linked_status == 0) {
        GLint infoLen = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLen);
        GL_CHECK();

        std::vector<char> infoLog(static_cast<size_t>(infoLen));
        glGetProgramInfoLog(programId, infoLen, nullptr, infoLog.data());
        GL_CHECK();

        std::cerr << "Error linking program:\n" << infoLog.data();
        glDeleteProgram(programId);
        GL_CHECK();
        return;
    }

    glDetachShader(programId, vertexShader);
    GL_CHECK();
    glDetachShader(programId, fragmentShader);
    GL_CHECK();

    glDeleteShader(vertexShader);
    GL_CHECK();
    glDeleteShader(fragmentShader);
    GL_CHECK();

    m_Program = programId;
}

GLuint OpenGLShader::compileShader(GLenum type, const std::string &source) {
    GLuint shader = glCreateShader(type);
    GL_CHECK();

    const char *sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    GL_CHECK();
    glCompileShader(shader);
    GL_CHECK();

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        GL_CHECK();

        std::vector<char> infoLog(static_cast<size_t>(infoLen));
        glGetShaderInfoLog(shader, infoLen, nullptr, infoLog.data());
        GL_CHECK();

        glDeleteShader(shader);
        GL_CHECK();

        std::cerr << "Error compiling shader(vertex)\n" << infoLog.data();
        return 0;
    }

    return shader;
}

void OpenGLShader::setInt(const std::string &name, int value) {
    bind();
    GLint location = glGetUniformLocation(m_Program, name.c_str());
    GL_CHECK();
    glUniform1i(location, value);
    GL_CHECK();
}

void OpenGLShader::setFloat(const std::string &name, float value) {
    bind();
    GLint location = glGetUniformLocation(m_Program, name.c_str());
    GL_CHECK();
    glUniform1f(location, value);
    GL_CHECK();
}

void OpenGLShader::setFloat2(const std::string &name, float value1,
                             float value2) {
    bind();
    GLint location = glGetUniformLocation(m_Program, name.c_str());
    GL_CHECK();
    glUniform2f(location, value1, value2);
    GL_CHECK();
}

void OpenGLShader::setFloat3(const std::string &name, float value1,
                             float value2, float value3) {
    bind();
    GLint location = glGetUniformLocation(m_Program, name.c_str());
    GL_CHECK();
    glUniform3f(location, value1, value2, value3);
    GL_CHECK();
}

void OpenGLShader::setMatrix4(const std::string &name,
                              const std::vector<float> &matrix) {
    bind();
    GLint location = glGetUniformLocation(m_Program, name.c_str());
    GL_CHECK();
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix.data());
    GL_CHECK();
}

void OpenGLShader::setMatrix2x3(const std::string &name,
                                const std::vector<float> &matrix) {
    bind();
    GLint location = glGetUniformLocation(m_Program, name.c_str());
    GL_CHECK();
    glUniformMatrix2x3fv(location, 1, GL_FALSE, matrix.data());
    GL_CHECK();
}

void OpenGLShader::setMatrix2(const std::string &name,
                              const std::vector<float> &matrix) {
    bind();
    GLint location = glGetUniformLocation(m_Program, name.c_str());
    GL_CHECK();
    glUniformMatrix2fv(location, 1, GL_FALSE, matrix.data());
    GL_CHECK();
}

} // namespace Engine