#pragma once

#include "ECS.hpp"

#include "Task.hpp"

namespace Engine {

class isVisitedTask : public Task {
  public:
    isVisitedTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        if (entity->hasComponent<VisitedComponent>()) {
            return TaskStatus::Success;
        }

        return TaskStatus::Fail;
    }
};

} // namespace Engine
