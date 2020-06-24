#pragma once

#include "DirectionComponent.hpp"
#include "LocationComponent.hpp"
#include "Task.hpp"

namespace Engine {

class LookAtTask : public Task {
  public:
    LookAtTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        auto target = blackboard->getPtr<Entity>("target");

        auto location = entity->getComponent<LocationComponent>();
        auto targetLocation = target->getComponent<LocationComponent>();

        int dx = targetLocation->x - location->x;

        auto direction = entity->getComponent<DirectionComponent>();

        direction->x = dx > 0 ? 1 : -1;

        return TaskStatus::Success;
    }
};

} // namespace Engine
