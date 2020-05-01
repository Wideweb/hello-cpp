#pragma once

#include "Entity.hpp"

namespace Engine {

enum class SlopeType { Left = 0, Right = 1 };

class SlopeComponent : public Component {
  public:
    SlopeType type;

    SlopeComponent(SlopeType type) : type(type) {}
};

} // namespace Engine