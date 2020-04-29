#include "Texture.hpp"
#include "OpenGLTexture.hpp"

namespace Engine {

Texture *Texture::create(const std::string &path) {
    return new OpenGLTexture(path);
}

} // namespace Engine