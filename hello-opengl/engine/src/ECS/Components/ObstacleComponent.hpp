#pragma once

#include "Entity.hpp"

namespace Engine {

class ObstacleComponent : public Component {
    virtual void serialize(std::ostringstream &out) override {
        out << "obstacle" << std::endl;
    }
};

} // namespace Engine