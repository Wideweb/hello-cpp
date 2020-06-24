#pragma once

#include "CollisionComponent.hpp"
#include "EnemyComponent.hpp"
#include "Task.hpp"

namespace Engine {

class HitByEnemyTask : public Task {
  public:
    HitByEnemyTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto collision = entity->getComponent<CollisionComponent>();
        if (collision->entity != nullptr &&
            collision->entity->hasComponent<EnemyComponent>()) {
            return TaskStatus::Success;
        }

        return TaskStatus::Fail;
    }
};

} // namespace Engine
