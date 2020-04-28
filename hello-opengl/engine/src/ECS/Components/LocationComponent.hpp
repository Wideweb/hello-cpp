#pragma once

#include "Entity.hpp"

namespace Engine {

class LocationComponent : public Component {
  public:
    float x;
    float y;
    float angleRad;

    LocationComponent(float x, float y, int angleDeg) : x(x), y(y) {
        angleRad = 3.14 * angleDeg / 180;
    }
};

} // namespace Engine