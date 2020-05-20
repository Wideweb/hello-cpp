#include "ShaderManager.hpp"
#include "File.hpp"

namespace Engine {

void ShaderManager::load(const std::string &name, const std::string &vertexPath,
                         const std::string &fragmentPath) {

    std::string vertexSrc = File::read(vertexPath);
    std::string fragmentSrc = File::read(fragmentPath);

    m_Map[name].reset(Shader::create(vertexSrc, fragmentSrc));
}

std::shared_ptr<Shader> ShaderManager::get(const std::string &name) {
    return m_Map[name];
}

} // namespace Engine
