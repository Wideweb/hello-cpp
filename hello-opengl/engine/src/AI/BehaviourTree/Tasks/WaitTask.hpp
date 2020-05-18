#pragma once

#include "FrameAnimationComponent.hpp"
#include "Task.hpp"
#include "VelocityComponent.hpp"
#include <iostream>

namespace Engine {

class WaitTask : public Task {
  public:
    WaitTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        auto animation = entity->getComponent<FrameAnimationComponent>();
        animation->play("wait");

        auto velocity = entity->getComponent<VelocityComponent>();
        velocity->x = 0;

        return TaskStatus::Success;
    }
};

} // namespace Engine
