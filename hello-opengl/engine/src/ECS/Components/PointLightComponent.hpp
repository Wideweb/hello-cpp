#pragma once

#include "Entity.hpp"
#include "Math.hpp"

namespace Engine {

class PointLightComponent : public Component {
  public:
    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    float constant = 0.2f;
    float linear = 0;
    float quadratic = 0.4;

    std::string shader;

    PointLightComponent(const std::string &shader) : shader(shader) {
        ambient = Vec3(0.0f, 0.0f, 0.0f);
        diffuse = Vec3(0.5f, 0.5f, 0.5f);
        specular = Vec3(1.0f, 0.3f, 0.3f);
    }
};

} // namespace Engine