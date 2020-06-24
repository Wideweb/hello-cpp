#pragma once

#include "Entity.hpp"
#include "Math.hpp"

namespace Engine {

class DirectionComponent : public Component {
  public:
    int x;
    int y;

    DirectionComponent(int x, int y) : x(x), y(y) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "direction"
            << " " << x << " " << y << std::endl;
    }
};

} // namespace Engine