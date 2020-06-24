#pragma once

#include "CollisionComponent.hpp"
#include "SteeringComponent.hpp"
#include "Task.hpp"

namespace Engine {

class StopSteeringTask : public Task {
  public:
    StopSteeringTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto steering = entity->getComponent<SteeringComponent>();
        if (steering) {
            steering->isActive = false;
        }

        return TaskStatus::Success;
    }
};

} // namespace Engine
