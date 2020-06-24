#pragma once

#include "Task.hpp"

#include <cmath>

namespace Engine {

class DeactivateTask : public Task {
  public:
    DeactivateTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        entity->isActive = false;

        return TaskStatus::Success;
    }
};

} // namespace Engine
