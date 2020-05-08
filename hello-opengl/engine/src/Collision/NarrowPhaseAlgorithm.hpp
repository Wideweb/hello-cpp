#pragma once

#include "CollisionShape.hpp"
#include <vector>

namespace Engine {

class NarrowPhaseAlgorithm {
  public:
    Vec2 collide(const CollisionShape &shape1, const CollisionShape &shape2);

  private:
    std::vector<Vec2> getAxis(const std::vector<Vec2> &corners);
};

} // namespace Engine
