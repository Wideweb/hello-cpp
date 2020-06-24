#pragma once

#include "LocationComponent.hpp"
#include "Task.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

class RespawnTask : public Task {
  public:
    RespawnTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto die = entity->getComponent<DieComponent>();
        if (die) {
            die->isActive = false;
        }

        return TaskStatus::Success;
    }
};

} // namespace Engine
