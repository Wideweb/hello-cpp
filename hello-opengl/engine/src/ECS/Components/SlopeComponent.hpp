#pragma once

#include "Entity.hpp"

namespace Engine {

enum class SlopeType { None = 0, Left = 1, Right = 2 };

class SlopeComponent : public Component {
  public:
    SlopeType type;

    SlopeComponent(SlopeType type) : type(type) {}
};

} // namespace Engine