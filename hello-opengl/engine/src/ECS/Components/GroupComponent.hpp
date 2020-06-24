#pragma once

#include "Entity.hpp"

namespace Engine {

class GroupComponent : public Component {
  public:
    std::string group;

    GroupComponent(const std::string &group) : group(group) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "group " << group << std::endl;
    }
};

} // namespace Engine