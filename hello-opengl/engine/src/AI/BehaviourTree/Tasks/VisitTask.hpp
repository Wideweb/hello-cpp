#pragma once

#include "ECS.hpp"

#include "Task.hpp"

namespace Engine {

class VisitTask : public Task {
  public:
    VisitTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        if (!entity->hasComponent<VisitedComponent>()) {
            entity->addComponent<VisitedComponent>();
        }

        return TaskStatus::Success;
    }
};

} // namespace Engine
