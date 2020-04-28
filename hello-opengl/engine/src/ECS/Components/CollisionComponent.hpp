#pragma once

#include "Entity.hpp"

namespace Engine {

class CollisionComponent : public Component {
  public:
    int width;
    int height;
    CollisionComponent(int width, int height) : width(width), height(height) {}
};

} // namespace Engine