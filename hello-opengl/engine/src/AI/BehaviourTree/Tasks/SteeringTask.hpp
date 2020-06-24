#pragma once

#include "CollisionComponent.hpp"
#include "FrameAnimationComponent.hpp"
#include "SteeringComponent.hpp"
#include "Task.hpp"

namespace Engine {

class SteeringTask : public Task {
  public:
    SteeringTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        auto target = blackboard->getPtr<Entity>("target");

        auto steering = entity->getComponent<SteeringComponent>();
        if (!steering) {
            entity->addComponent<SteeringComponent>(target->getName());
        } else {
            steering->isActive = true;
        }

        auto animation = entity->getComponent<FrameAnimationComponent>();
        animation->play("wait");

        return TaskStatus::Success;
    }
};

} // namespace Engine
