#pragma once

#include "Entity.hpp"
#include "Math.hpp"

namespace Engine {

class SpotLightComponent : public Component {
  public:
    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    Vec2 direction;
    float constant = 0.2f;
    float linear = 0;
    float quadratic = 0.4;
    float cutOff;
    float outerCutOff;

    SpotLightComponent(const Vec3 &ambient, const Vec3 &diffuse,
                       const Vec3 &specular, float constant, float linear,
                       float quadratic, const Vec2 &direction, float cutOff,
                       float outerCutOff)
        : ambient(ambient), diffuse(diffuse), specular(specular),
          constant(constant), linear(linear), quadratic(quadratic),
          direction(direction), cutOff(cutOff), outerCutOff(outerCutOff) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "spotLight ";
        out << ambient << " ";
        out << diffuse << " ";
        out << direction << " ";
        out << constant << " ";
        out << linear << " ";
        out << quadratic << " ";
        out << cutOff << " ";
        out << outerCutOff << " ";
    }
};

} // namespace Engine