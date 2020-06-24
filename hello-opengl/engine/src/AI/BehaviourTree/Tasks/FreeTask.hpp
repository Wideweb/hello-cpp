#pragma once

#include "Task.hpp"

namespace Engine {

class FreeTask : public Task {
  public:
    FreeTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        entity->isActive = false;

        return TaskStatus::Success;
    }
};

} // namespace Engine
