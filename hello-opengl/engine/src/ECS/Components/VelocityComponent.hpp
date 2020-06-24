#pragma once

#include "Entity.hpp"

namespace Engine {

class VelocityComponent : public Component {
  public:
    float xMax;
    float x;
    float y;

    VelocityComponent(float x, float y) : x(x), y(y), xMax(x) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "velocity ";
        out << x << " ";
        out << y << " ";
        out << std::endl;
    }
};

} // namespace Engine