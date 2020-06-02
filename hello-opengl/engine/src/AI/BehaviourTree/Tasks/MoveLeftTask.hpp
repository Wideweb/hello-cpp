#pragma once

#include "FrameAnimationComponent.hpp"
#include "LocationComponent.hpp"
#include "SpotLightComponent.hpp"
#include "Task.hpp"
#include "TextureComponent.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

class MoveLeftTask : public Task {
  public:
    MoveLeftTask() {}

    TaskStatus update(std::shared_ptr<Blackboard> blackboard) override {
        auto entity = blackboard->getPtr<Entity>("entity");

        auto velocity = entity->getComponent<VelocityComponent>();
        velocity->x = blackboard->getFloat("speedX") * -1;

        auto texture = entity->getComponent<TextureComponent>();
        texture->flip = Flip::None;

        auto light = entity->getComponent<SpotLightComponent>();
        light->direction.x = -1;

        auto animation = entity->getComponent<FrameAnimationComponent>();
        animation->play("move");

        return TaskStatus::Success;
    }
};

} // namespace Engine
