#pragma once

#include <string>

namespace Engine {

class Shader {
  public:
    virtual ~Shader() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void SetFloat(const std::string &name, float value) = 0;
    virtual void SetFloat2(const std::string &name, float value,
                           float value2) = 0;

    static Shader *create(const std::string &vertexSrc,
                          const std::string &fragmentSrc);
};

} // namespace Engine