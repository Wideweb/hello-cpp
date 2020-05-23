#pragma once

#include "Texture.hpp"
#include "glad/glad.h"

namespace Engine {

class OpenGLTexture : public Texture {
  private:
    GLuint m_TextureID;

  public:
    OpenGLTexture(const void *pixels, const size_t width, const size_t height);
    OpenGLTexture(const std::string &path);
    virtual ~OpenGLTexture();

    virtual void bind() override;
    virtual void unbind() override;

  private:
    bool load(const std::string &path);
};

} // namespace Engine
