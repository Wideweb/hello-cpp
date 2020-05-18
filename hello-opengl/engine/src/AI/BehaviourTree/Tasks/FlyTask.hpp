#pragma once

#include "FrameAnimationComponent.hpp"
#include "Task.hpp"

namespace Engine {

class FlyTask : public Task {
  public:
    FlyTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        auto animation = entity->getComponent<FrameAnimationComponent>();
        animation->play("wait");

        return TaskStatus::Success;
    }
};

} // namespace Engine
