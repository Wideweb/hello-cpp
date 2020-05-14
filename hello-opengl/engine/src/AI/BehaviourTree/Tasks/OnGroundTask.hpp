#pragma once

#include "CollisionComponent.hpp"
#include "GroundComponent.hpp"
#include "Task.hpp"

namespace Engine {

class OnGroundTask : public Task {
  public:
    OnGroundTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto collision = entity->getComponent<CollisionComponent>();
        if (collision->entity != nullptr &&
            collision->entity->hasComponent<GroundComponent>()) {
            return TaskStatus::Success;
        }

        return TaskStatus::Fail;
    }
};

} // namespace Engine
