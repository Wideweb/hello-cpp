#pragma once

#include <string>

namespace Engine {

class Texture {
  public:
    virtual ~Texture() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    static Texture *create(const std::string &path);
};

} // namespace Engine
