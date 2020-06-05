#pragma once

#include "FrameAnimationComponent.hpp"
#include "LocationComponent.hpp"
#include "Task.hpp"
#include "TextureComponent.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

class MoveRightTask : public Task {
  public:
    MoveRightTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto velocity = entity->getComponent<VelocityComponent>();
        velocity->x = blackboard->getFloat("speedX");

        auto texture = entity->getComponent<TextureComponent>();
        texture->flip = Flip::Y;

        auto animation = entity->getComponent<FrameAnimationComponent>();
        animation->play("move");

        return TaskStatus::Success;
    }
};

} // namespace Engine
