#pragma once

#include "Blackboard.hpp"
#include "Entity.hpp"
#include "Task.hpp"

namespace Engine {

class AIComponent : public Component {
  public:
    Task *tree;
    AIComponent(Task *tree) : tree(tree) {}

    virtual void serialize(std::ostringstream &out) override {}
};

} // namespace Engine