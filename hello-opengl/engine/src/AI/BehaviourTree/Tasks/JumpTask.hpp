#pragma once

#include "Task.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

class JumpTask : public Task {
  public:
    JumpTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto velocity = entity->getComponent<VelocityComponent>();
        velocity->y = blackboard->getFloat("speedY");

        return TaskStatus::Success;
    }
};

} // namespace Engine
