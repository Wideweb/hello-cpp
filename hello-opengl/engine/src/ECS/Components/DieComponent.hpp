#pragma once

#include "Entity.hpp"

namespace Engine {

class DieComponent : public Component {
  public:
    DieComponent() {}

    virtual void serialize(std::ostringstream &out) override {
        out << "die" << std::endl;
    }
};

} // namespace Engine