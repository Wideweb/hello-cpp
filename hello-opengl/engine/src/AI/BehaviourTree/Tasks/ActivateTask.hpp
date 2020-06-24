#pragma once

#include "LocationComponent.hpp"
#include "Task.hpp"

#include <cmath>

namespace Engine {

class ActivateTask : public Task {
  public:
    ActivateTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        entity->isActive = true;

        return TaskStatus::Success;
    }
};

} // namespace Engine
