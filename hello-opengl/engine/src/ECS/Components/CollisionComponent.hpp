#pragma once

#include "Entity.hpp"
#include <string>

namespace Engine {

struct BeginCollisionEvent {
    std::string first;
    std::string second;
};

struct EndCollisionEvent {
    std::string first;
    std::string second;
};

class CollisionComponent : public Component {
  public:
    int width;
    int height;
    CollisionComponent(int width, int height) : width(width), height(height) {}
};

} // namespace Engine