#pragma once

#include "Task.hpp"
#include "TextureComponent.hpp"

#include <cmath>

namespace Engine {

class HideTask : public Task {
  public:
    HideTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        entity->getComponent<TextureComponent>()->isActive = false;

        return TaskStatus::Success;
    }
};

} // namespace Engine
