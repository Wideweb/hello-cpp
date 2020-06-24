#pragma once

#include "Entity.hpp"

namespace Engine {

class GroundComponent : public Component {
  public:
    GroundComponent() {}

    virtual void serialize(std::ostringstream &out) override {
        out << "groud" << std::endl;
    }
};

} // namespace Engine