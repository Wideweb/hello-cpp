#pragma once

#include "Entity.hpp"

namespace Engine {

class ParentComponent : public Component {
  public:
    std::string parent;

    ParentComponent(const std::string &parent) : parent(parent) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "parent " << parent << std::endl;
    }
};

} // namespace Engine