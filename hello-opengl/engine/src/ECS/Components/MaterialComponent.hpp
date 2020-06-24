#pragma once

#include "Entity.hpp"
#include "Math.hpp"

namespace Engine {

class MaterialComponent : public Component {
  public:
    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    float shininess;

    MaterialComponent() {
        ambient = Vec3(1.0f, 1.0f, 1.0f);
        diffuse = Vec3(1.0f, 1.0f, 1.0f);
        specular = Vec3(1.0f, 1.0f, 1.0f);
        shininess = 32.0f;
    }

    virtual void serialize(std::ostringstream &out) override {
        out << "material ";
        out << ambient.x << " ";
        out << diffuse.x << " ";
        out << specular.x << " ";
        out << shininess;
        out << std::endl;
    }
};

} // namespace Engine