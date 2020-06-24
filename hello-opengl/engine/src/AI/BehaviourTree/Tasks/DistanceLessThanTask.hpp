#pragma once

#include "LocationComponent.hpp"
#include "Task.hpp"

#include <cmath>

namespace Engine {

class DistanceLessThanTask : public Task {
  public:
    DistanceLessThanTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto parent = blackboard->getPtr<Entity>("parent");
        auto entity = blackboard->getPtr<Entity>("entity");
        auto target = blackboard->getPtr<Entity>("target");
        auto distance = blackboard->getFloat("distance");

        auto location = entity->getComponent<LocationComponent>();
        auto targetLocation = target->getComponent<LocationComponent>();

        int x = location->x;

        if (parent) {
            auto parentLocation = parent->getComponent<LocationComponent>();
            x += parentLocation->x;
        }

        float d = std::abs(targetLocation->x - x);

        return d < distance ? TaskStatus::Success : TaskStatus::Fail;
    }
};

} // namespace Engine
