#pragma once

#include "Entity.hpp"

namespace Engine {

enum class Direction { Left = 0, Right = 1 };

class LocationComponent : public Component {
  public:
    float x;
    float y;
    Direction direction;

    LocationComponent(float x, float y, Direction direction = Direction::Left)
        : x(x), y(y), direction(direction) {}
};

} // namespace Engine