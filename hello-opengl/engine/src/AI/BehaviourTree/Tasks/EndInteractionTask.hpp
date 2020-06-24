#pragma once

#include "ECS.hpp"

#include "Task.hpp"

namespace Engine {

class EndInteractionTask : public Task {
  public:
    EndInteractionTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto interaction = entity->getComponent<InteractionComponent>();
        if (interaction) {
            interaction->isActive = false;
        }

        return TaskStatus::Success;
    }
};

} // namespace Engine
