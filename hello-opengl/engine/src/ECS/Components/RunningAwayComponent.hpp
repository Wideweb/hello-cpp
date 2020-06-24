#pragma once

#include "Entity.hpp"

namespace Engine {

class RunningAwayComponent : public Component {
  public:
    RunningAwayComponent() {}

    virtual void serialize(std::ostringstream &out) override {
        out << "runningAway" << std::endl;
    }
};

} // namespace Engine