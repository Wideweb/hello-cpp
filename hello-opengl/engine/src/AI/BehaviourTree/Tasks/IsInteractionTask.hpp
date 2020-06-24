#pragma once

#include "ECS.hpp"

#include "Task.hpp"

namespace Engine {

class IsInteractionTask : public Task {
  public:
    IsInteractionTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto interaction = entity->getComponent<InteractionComponent>();
        if (interaction && interaction->isActive) {
            return TaskStatus::Success;
        }

        return TaskStatus::Fail;
    }
};

} // namespace Engine
