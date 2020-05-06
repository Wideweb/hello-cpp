#pragma once

#include "Entity.hpp"

namespace Engine {

class CameraComponent : public Component {
  public:
    int leftBound;
    int rightBound;
    int offset;
    CameraComponent(int leftBound, int rightBound, int offset)
        : leftBound(leftBound), rightBound(rightBound), offset(offset) {}
};

} // namespace Engine