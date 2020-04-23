#include "Shader.hpp"
#include "OpenGLShader.hpp"

namespace Engine {

Shader *Shader::create(const std::string &vertexSrc,
                       const std::string &fragmentSrc) {
    return new OpenGLShader(vertexSrc, fragmentSrc);
}

} // namespace Engine