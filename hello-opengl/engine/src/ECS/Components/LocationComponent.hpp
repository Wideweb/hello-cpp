#pragma once

#include "Entity.hpp"

namespace Engine {

class LocationComponent : public Component {
  public:
    float x;
    float y;
    float scale = 1.0;
    float angle = 0.0;

    LocationComponent(float x, float y) : x(x), y(y) {}
};

} // namespace Engine