#include "OpenGLShader.hpp"
#include <iostream>
#include <vector>

namespace Engine {

OpenGLShader::OpenGLShader(const std::string &vertexSrc,
                           const std::string &fragmentSrc) {
    compile(vertexSrc, fragmentSrc);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(m_Program); };

void OpenGLShader::bind() { glUseProgram(m_Program); }
void OpenGLShader::unbind() { glUseProgram(0); }

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
    if (programId == 0) {
        std::cerr << "failed to create gl program";
        return;
    }

    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);

    glLinkProgram(programId);
    GLint linked_status = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &linked_status);
    if (linked_status == 0) {
        GLint infoLen = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLen);

        std::vector<char> infoLog(static_cast<size_t>(infoLen));
        glGetProgramInfoLog(programId, infoLen, nullptr, infoLog.data());

        std::cerr << "Error linking program:\n" << infoLog.data();
        glDeleteProgram(programId);
        return;
    }

    glDetachShader(programId, vertexShader);
    glDetachShader(programId, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_Program = programId;
}

GLuint OpenGLShader::compileShader(GLenum type, const std::string &source) {
    GLuint shader = glCreateShader(type);

    const char *sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        std::vector<char> infoLog(static_cast<size_t>(infoLen));
        glGetShaderInfoLog(shader, infoLen, nullptr, infoLog.data());

        glDeleteShader(shader);

        std::cerr << "Error compiling shader(vertex)\n" << infoLog.data();
        return 0;
    }

    return shader;
}

} // namespace Engine