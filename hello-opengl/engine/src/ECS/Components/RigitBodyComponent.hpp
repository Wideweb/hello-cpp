#pragma once

#include "Entity.hpp"

namespace Engine {

class RigitBodyComponent : public Component {
  public:
    float weight;

    RigitBodyComponent(float weight) : weight(weight) {}
};

} // namespace Engine