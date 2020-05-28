#pragma once

#include <string>
#include <vector>

namespace Engine {

class Shader {
  public:
    virtual ~Shader() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void setInt(const std::string &name, int value) = 0;

    virtual void setFloat(const std::string &name, float value) = 0;
    virtual void setFloat2(const std::string &name, float value,
                           float value2) = 0;
    virtual void setFloat3(const std::string &name, float value, float value2,
                           float value3) = 0;
    virtual void setMatrix4(const std::string &name,
                            const std::vector<float> &matrix) = 0;

    virtual void setMatrix2x3(const std::string &name,
                              const std::vector<float> &matrix) = 0;

    virtual void setMatrix2(const std::string &name,
                            const std::vector<float> &matrix) = 0;

    static Shader *create(const std::string &vertexSrc,
                          const std::string &fragmentSrc);
};

} // namespace Engine