#pragma once

#include "AnimationComponent.hpp"
#include "Task.hpp"
#include "VelocityComponent.hpp"
#include <iostream>

namespace Engine {

class WaitTask : public Task {
  public:
    WaitTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        auto animation = entity->getComponent<AnimationComponent>();
        animation->play("wait");

        auto velocity = entity->getComponent<VelocityComponent>();
        velocity->x = 0;

        std::cout << "wait" << std::endl;

        return TaskStatus::Success;
    }
};

} // namespace Engine
