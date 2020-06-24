#pragma once

#include "Entity.hpp"

namespace Engine {

class LocationComponent : public Component {
  public:
    float x = 0;
    float y = 0;
    float scale = 1.0;
    float angle = 0.0;

    LocationComponent(float x, float y) : x(x), y(y) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "location ";
        out << x << " " << y;
        out << std::endl;
    }
};

} // namespace Engine