#pragma once

#include "ECS.hpp"

#include "Task.hpp"

namespace Engine {

class BeginInteractionTask : public Task {
  public:
    BeginInteractionTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto interaction = entity->getComponent<InteractionComponent>();
        if (interaction) {
            interaction->isActive = true;
        } else {
            entity->addComponent<InteractionComponent>();
        }

        return TaskStatus::Success;
    }
};

} // namespace Engine
