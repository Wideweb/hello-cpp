#pragma once

#include "Entity.hpp"

namespace Engine {

class RigitBodyComponent : public Component {
  public:
    float weight;

    RigitBodyComponent(float weight) : weight(weight) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "rigitBody " << weight << std::endl;
    }
};

} // namespace Engine