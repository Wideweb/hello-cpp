#pragma once

#include "Entity.hpp"

namespace Engine {

class InteractionComponent : public Component {
  public:
    InteractionComponent() {}

    virtual void serialize(std::ostringstream &out) override {
        out << "interaction" << std::endl;
    }
};

} // namespace Engine