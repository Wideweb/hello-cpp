#pragma once

#include <string>

namespace Engine {

class Texture {
  public:
    virtual ~Texture() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    static Texture *create(const std::string &path);
    static Texture *create(const void *pixels, const size_t width,
                           const size_t height);
};

} // namespace Engine
