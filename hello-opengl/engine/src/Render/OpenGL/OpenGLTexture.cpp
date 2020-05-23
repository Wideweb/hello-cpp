#include "OpenGLTexture.hpp"
#include "Debug.hpp"
#include "picopng.hpp"

namespace Engine {

OpenGLTexture::OpenGLTexture(const void *pixels, const size_t width,
                             const size_t height) {
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    GLint mipmap_level = 0;
    GLint border = 0;

    // clang-format off
    glTexImage2D(
        GL_TEXTURE_2D,
        mipmap_level,
        GL_RGBA,
        static_cast<GLsizei>(width),
        static_cast<GLsizei>(height),
        border,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pixels
    );
    // clang-format on

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

OpenGLTexture::OpenGLTexture(const std::string &path) { load(path); }

bool OpenGLTexture::load(const std::string &path) {
    std::vector<std::byte> fileInMemory;
    std::ifstream in(path.data(), std::ios_base::binary);

    if (!in) {
        return false;
    }

    in.seekg(0, std::ios_base::end);
    size_t fileSize = static_cast<size_t>(in.tellg());
    fileInMemory.resize(fileSize);
    in.seekg(0, std::ios_base::beg);

    if (!in) {
        return false;
    }

    in.read(reinterpret_cast<char *>(fileInMemory.data()),
            static_cast<std::streamsize>(fileInMemory.size()));

    if (!in.good()) {
        return false;
    }

    std::vector<std::byte> image;
    unsigned long width = 0;
    unsigned long height = 0;
    int error = decodePNG(image, width, height, &fileInMemory[0],
                          fileInMemory.size(), false);

    if (error != 0) {
        std::cerr << "error: " << error << std::endl;
        return false;
    }

    glGenTextures(1, &m_TextureID);
    GL_CHECK()
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    GL_CHECK()

    GLint mipmapLevel = 0;
    GLint border = 0;

    // clang-format off
    glTexImage2D(GL_TEXTURE_2D,    // Specifies the target texture of the active texture unit
                 mipmapLevel,      // Specifies the level-of-detail number. Level 0 is the base image level
                 GL_RGBA,          // Specifies the internal format of the texture
                 static_cast<GLsizei>(width),
                 static_cast<GLsizei>(height),
                 border,           // Specifies the width of the border. Must be 0. For GLES 2.0
                 GL_RGBA,          // Specifies the format of the texel data. Must match internalformat
                 GL_UNSIGNED_BYTE, // Specifies the data type of the texel data
                 image.data());       // Specifies a pointer to the image data in memory
    // clang-format on
    GL_CHECK()

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL_CHECK()
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_BLEND);
    GL_CHECK()
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GL_CHECK()

    glBindTexture(GL_TEXTURE_2D, 0);
    GL_CHECK();

    return true;
}

void OpenGLTexture::bind() {
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    GL_CHECK();
}

void OpenGLTexture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    GL_CHECK();
}

OpenGLTexture::~OpenGLTexture() {
    glDeleteTextures(1, &m_TextureID);
    GL_CHECK();
}

} // namespace Engine
