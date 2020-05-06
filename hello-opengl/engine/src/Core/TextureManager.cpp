#include "TextureManager.hpp"

namespace Engine {

void TextureManager::load(const std::string &name, const std::string &path) {
    m_Map[name].reset(Texture::create(path));
}

std::shared_ptr<Texture> TextureManager::get(const std::string &name) {
    return m_Map[name];
}

} // namespace Engine
