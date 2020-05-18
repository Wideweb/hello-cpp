#pragma once

#include "Entity.hpp"

namespace Engine {

class ParalaxScrollingComponent : public Component {
  public:
    float scale = 1.0;

    ParalaxScrollingComponent(float scale) : scale(scale) {}
};

} // namespace Engine