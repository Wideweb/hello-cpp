#pragma once

#include <string>

namespace Engine {

class Shader {
  public:
    virtual ~Shader(){};

    virtual void bind() = 0;
    virtual void unbind() = 0;

    static Shader *create(const std::string &vertexSrc,
                          const std::string &fragmentSrc);
};

} // namespace Engine