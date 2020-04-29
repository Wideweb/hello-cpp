#include "OpenGLTexture.hpp"
#include "Debug.hpp"
#include "picopng.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace Engine {

OpenGLTexture::OpenGLTexture(const std::string &path) { load(path); }

bool OpenGLTexture::load(const std::string &path) {
    std::vector<std::byte> fileInMemory;
    std::ifstream fin(path.data(), std::ios_base::binary);

    if (!fin) {
        return false;
    }

    fin.seekg(0, std::ios_base::end);
    size_t fileSize = static_cast<size_t>(fin.tellg());
    fileInMemory.resize(fileSize);
    fin.seekg(0, std::ios_base::beg);

    if (!fin) {
        return false;
    }

    fin.read(reinterpret_cast<char *>(fileInMemory.data()),
             static_cast<std::streamsize>(fileInMemory.size()));

    if (!fin.good()) {
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
