#pragma once

#include "AnimationComponent.hpp"
#include "Task.hpp"

namespace Engine {

class FlyTask : public Task {
  public:
    FlyTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        auto animation = entity->getComponent<AnimationComponent>();
        animation->play("wait");

        return TaskStatus::Success;
    }
};

} // namespace Engine
