#pragma once

#include "Entity.hpp"

namespace Engine {

class VelocityComponent : public Component {
  public:
    float x;
    float y;

    VelocityComponent(float x, float y) : x(x), y(y) {}
};

} // namespace Engine