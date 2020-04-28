#pragma once

#include "LocationComponent.hpp"
#include "Task.hpp"
#include "VelocityComponent.hpp"
#include "cmath"

namespace Engine {

class MoveTask : public Task {
  public:
    MoveTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        float x = blackboard->getFloat("targetX");
        float y = blackboard->getFloat("targetY");

        auto location = entity->getComponent<LocationComponent>();
        auto velocity = entity->getComponent<VelocityComponent>();

        float dx = x - location->x;
        float dy = y - location->y;

        int dxSign = dx > 0 ? 1 : -1;
        int dySign = dy > 0 ? 1 : -1;

        float d2x = dx * dx;
        float d2y = dy * dy;

        float distance = d2x + d2y;
        float targetSpeed = 2;

        if (distance < targetSpeed) {
            return TaskStatus::Success;
        }

        float targetVelocityX = dxSign * d2x / distance * targetSpeed;
        float targetVelocityY = dySign * d2y / distance * targetSpeed;

        velocity->x = targetVelocityX;
        velocity->y = targetVelocityY;

        return TaskStatus::Running;
    }
};

} // namespace Engine
