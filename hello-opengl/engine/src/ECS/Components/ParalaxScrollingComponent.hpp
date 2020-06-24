#pragma once

#include "Entity.hpp"

namespace Engine {

class ParalaxScrollingComponent : public Component {
  public:
    float scale = 1.0;

    ParalaxScrollingComponent(float scale) : scale(scale) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "paralax " << scale << std::endl;
    }
};

} // namespace Engine