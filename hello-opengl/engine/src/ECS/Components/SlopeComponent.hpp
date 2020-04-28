#pragma once

#include "Entity.hpp"

namespace Engine {

class SlopeComponent : public Component {
  public:
    bool left;
    bool right;

    SlopeComponent(float left) : left(left), right(!left) {}
};

} // namespace Engine