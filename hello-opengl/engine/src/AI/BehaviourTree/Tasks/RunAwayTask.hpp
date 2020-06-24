#pragma once

#include "DirectionComponent.hpp"
#include "FrameAnimationComponent.hpp"
#include "LocationComponent.hpp"
#include "RunningAwayComponent.hpp"
#include "Task.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

class RunAwayTask : public Task {
  public:
    RunAwayTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        auto target = blackboard->getPtr<Entity>("target");
        auto speed = blackboard->getFloat("runSpeed");
        auto distance = blackboard->getFloat("runDistance");

        auto location = entity->getComponent<LocationComponent>();
        auto velocity = entity->getComponent<VelocityComponent>();
        auto targetLocation = target->getComponent<LocationComponent>();

        float dx = location->x - targetLocation->x;
        int sign = dx > 0 ? 1 : -1;
        velocity->x = sign * speed;

        auto direction = entity->getComponent<DirectionComponent>();
        direction->x = sign;

        auto animation = entity->getComponent<FrameAnimationComponent>();
        animation->play("move");

        if (!entity->hasComponent<RunningAwayComponent>()) {
            entity->addComponent<RunningAwayComponent>();
        }

        if (dx * sign < distance) {
            return TaskStatus::Running;
        } else {
            return TaskStatus::Success;
        }
    }
};

} // namespace Engine
