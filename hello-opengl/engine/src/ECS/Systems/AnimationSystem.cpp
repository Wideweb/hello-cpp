#include "AnimationSystem.hpp"
#include "AnimationComponent.hpp"
#include "Application.hpp"
#include "FrameAnimationComponent.hpp"
#include "LocationComponent.hpp"
#include "Math.hpp"
#include "TextureComponent.hpp"
#include "VelocityComponent.hpp"
#include "cmath"

namespace Engine {

void AnimationSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    float time = Application::get().getTime().getDeltaSeconds();

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<FrameAnimationComponent>()) {
            auto animation = entity->getComponent<FrameAnimationComponent>();
            auto velocity = entity->getComponent<VelocityComponent>();

            FrameAnimation &current = animation->getCurrent();

            animation->frameElapsedTime += time;
            if (animation->frameElapsedTime > current.frameTime) {
                animation->frameElapsedTime -= current.frameTime;
                animation->frameIndex++;
            }

            if (animation->frameIndex == current.framesNumber) {
                animation->frameIndex = 0;
            }
        }

        if (entity->hasComponent<AnimationComponent>()) {
            auto animation = entity->getComponent<AnimationComponent>();
            auto location = entity->getComponent<LocationComponent>();

            auto steps = animation->scene.step(time);
            for (auto &step : steps) {
                switch (step.property) {
                case AnimationProperty::X:
                    location->x += step.value;
                    break;
                case AnimationProperty::Y:
                    location->y += step.value;
                    break;
                case AnimationProperty::Scale:
                    location->scale += step.value;
                    break;
                case AnimationProperty::Angle:
                    location->angle += step.value;
                    break;

                default:
                    break;
                }
            }
        }
    }
}

} // namespace Engine
