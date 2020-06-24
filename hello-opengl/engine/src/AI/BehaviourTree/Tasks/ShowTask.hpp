#pragma once

#include "Task.hpp"
#include "TextureComponent.hpp"

#include <cmath>

namespace Engine {

class ShowTask : public Task {
  public:
    ShowTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        entity->getComponent<TextureComponent>()->isActive = true;

        return TaskStatus::Success;
    }
};

} // namespace Engine
