#pragma once

#include "FrameAnimationComponent.hpp"
#include "LocationComponent.hpp"
#include "Task.hpp"

namespace Engine {

class MoveTask : public Task {
  public:
    MoveTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto animation = entity->getComponent<FrameAnimationComponent>();
        animation->play("move");

        return TaskStatus::Success;
    }
};

} // namespace Engine
