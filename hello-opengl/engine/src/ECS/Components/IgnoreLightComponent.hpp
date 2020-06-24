#pragma once

#include "Entity.hpp"

namespace Engine {

class IgnoreLightComponent : public Component {
  public:
    IgnoreLightComponent() {}

    virtual void serialize(std::ostringstream &out) override {
        out << "ignoreLight" << std::endl;
    }
};

} // namespace Engine