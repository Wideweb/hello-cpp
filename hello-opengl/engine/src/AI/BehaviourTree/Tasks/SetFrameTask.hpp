#pragma once

#include "FrameComponent.hpp"

#include "Task.hpp"

namespace Engine {

class SetFrameTask : public Task {
  public:
    SetFrameTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        int frame = blackboard->getInt("frame");

        entity->getComponent<FrameComponent>()->index = frame;

        return TaskStatus::Success;
    }
};

} // namespace Engine
