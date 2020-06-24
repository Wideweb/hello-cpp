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

    PointLightComponent(const Vec3 &ambient, const Vec3 &diffuse,
                        const Vec3 &specular, float constant, float linear,
                        float quadratic)
        : ambient(ambient), diffuse(diffuse), specular(specular),
          constant(constant), linear(linear), quadratic(quadratic) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "pointLight ";
        out << ambient << " ";
        out << diffuse << " ";
        out << specular << " ";
        out << constant << " ";
        out << linear << " ";
        out << quadratic << " ";
        out << std::endl;
    }
};

} // namespace Engine