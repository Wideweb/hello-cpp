#pragma once

#include "DieComponent.hpp"
#include "GroundComponent.hpp"
#include "Task.hpp"

namespace Engine {

class DieTask : public Task {
  public:
    DieTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto die = entity->getComponent<DieComponent>();
        if (die && die->isActive) {
            return TaskStatus::Success;
        }

        return TaskStatus::Fail;
    }
};

} // namespace Engine
