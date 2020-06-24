#pragma once

#include "CollisionComponent.hpp"
#include "GroundCollisionComponent.hpp"
#include "GroundComponent.hpp"
#include "Task.hpp"

namespace Engine {

class OnGroundTask : public Task {
  public:
    OnGroundTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto collision = entity->getComponent<CollisionComponent>();
        auto groundCollision = entity->getComponent<GroundCollisionComponent>();

        if (collision && collision->entity != nullptr &&
            collision->entity->hasComponent<GroundComponent>()) {
            return TaskStatus::Success;
        }

        if (groundCollision != nullptr && groundCollision->onGround) {
            return TaskStatus::Success;
        }

        return TaskStatus::Fail;
    }
};

} // namespace Engine
