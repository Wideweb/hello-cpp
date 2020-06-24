#include "AnimationSystem.hpp"
#include "AnimationComponent.hpp"
#include "Application.hpp"
#include "FrameAnimationComponent.hpp"
#include "LocationComponent.hpp"
#include "Math.hpp"
#include "PointLightComponent.hpp"
#include "SpotLightComponent.hpp"
#include "TextureComponent.hpp"
#include "VelocityComponent.hpp"
#include "cmath"

namespace Engine {

void AnimationSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    float time = Application::get().getTime().getDeltaSeconds();
    auto &sound = Application::get().getSound();

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

            if (!animation->isActive) {
                continue;
            }

            auto location = entity->getComponent<LocationComponent>();
            auto texture = entity->getComponent<TextureComponent>();
            auto light = entity->getComponent<PointLightComponent>();

            auto steps = animation->scene.step(time);
            for (auto &step : steps) {

                if (step.action == ActionType::PlayMusic) {
                    sound.play(step.sound, 1.0, SoundBuffer::Properties::Once);
                    continue;
                }

                if (step.action == ActionType::Active) {
                    entity->getComponent<SpotLightComponent>()->isActive = true;
                    continue;
                }

                if (step.action == ActionType::Inactive) {
                    entity->getComponent<SpotLightComponent>()->isActive =
                        false;
                    continue;
                }

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
                case AnimationProperty::Alpha:
                    texture->alpha += step.value;
                    break;
                case AnimationProperty::Diffuse:
                    light->diffuse.x += step.value;
                    light->diffuse.y += step.value;
                    light->diffuse.z += step.value;
                    break;
                case AnimationProperty::Specular:
                    light->specular.x += step.value;
                    light->specular.y += step.value;
                    light->specular.z += step.value;
                    break;
                case AnimationProperty::Ambient:
                    light->ambient.x += step.value;
                    light->ambient.y += step.value;
                    light->ambient.z += step.value;
                    break;

                default:
                    break;
                }
            }
        }
    }
}

} // namespace Engine
