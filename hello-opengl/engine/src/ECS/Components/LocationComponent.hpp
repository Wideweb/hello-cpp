#pragma once

#include "Entity.hpp"

namespace Engine {

class LocationComponent : public Component {
  public:
    float x;
    float y;
    float scale = 1.0;
    float angle = 0.0;
    bool isStatic;

    LocationComponent(float x, float y, bool isStatic = false)
        : x(x), y(y), isStatic(isStatic) {}
};

} // namespace Engine