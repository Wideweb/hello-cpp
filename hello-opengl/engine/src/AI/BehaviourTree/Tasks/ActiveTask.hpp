#pragma once

#include "Task.hpp"

namespace Engine {

class ActiveTask : public Task {
  public:
    ActiveTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        return entity->isActive ? TaskStatus::Success : TaskStatus::Fail;
    }
};

} // namespace Engine
