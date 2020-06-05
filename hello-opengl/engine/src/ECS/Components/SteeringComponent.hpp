#pragma once

#include "Entity.hpp"

namespace Engine {

class SteeringComponent : public Component {
  public:
    std::string target;

    SteeringComponent(const std::string &target) : target(target) {}
};

} // namespace Engine