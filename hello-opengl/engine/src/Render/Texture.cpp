#include "Texture.hpp"
#include "OpenGLTexture.hpp"

namespace Engine {

Texture *Texture::create(const std::string &path) {
    return new OpenGLTexture(path);
}

Texture *Texture::create(const void *pixels, const size_t width,
                         const size_t height) {
    return new OpenGLTexture(pixels, width, height);
}

} // namespace Engine