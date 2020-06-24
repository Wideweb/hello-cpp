#pragma once

#include "FrameAnimationComponent.hpp"
#include "Task.hpp"
#include "VelocityComponent.hpp"
#include <iostream>

namespace Engine {

class WaitTask : public Task {
  private:
    float m_Elapsed = 0;

  public:
    WaitTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");
        float wait = blackboard->getFloat("wait");

        auto animation = entity->getComponent<FrameAnimationComponent>();
        animation->play("wait");

        auto velocity = entity->getComponent<VelocityComponent>();
        velocity->x = 0;

        if (m_Elapsed < wait) {
            m_Elapsed += Application::get().getTime().getDeltaSeconds();
            return TaskStatus::Running;
        }

        m_Elapsed = 0;
        return TaskStatus::Success;
    }
};

} // namespace Engine
