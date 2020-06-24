#pragma once

#include "Entity.hpp"

namespace Engine {

class SteeringComponent : public Component {
  public:
    std::string target;

    SteeringComponent(const std::string &target) : target(target) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "steering " << target << std::endl;
    }
};

} // namespace Engine