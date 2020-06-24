#pragma once

#include "Entity.hpp"

namespace Engine {

class VisitedComponent : public Component {
  public:
    VisitedComponent() {}

    virtual void serialize(std::ostringstream &out) override {
        out << "visited" << std::endl;
    }
};

} // namespace Engine