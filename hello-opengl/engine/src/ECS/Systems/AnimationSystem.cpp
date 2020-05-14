#include "AnimationSystem.hpp"
#include "AnimationComponent.hpp"
#include "Application.hpp"
#include "Math.hpp"
#include "TextureComponent.hpp"
#include "VelocityComponent.hpp"
#include "cmath"

namespace Engine {

void AnimationSystem::exec(EntityManager &entities) {
    auto &render = Application::get().getRender();
    float time = Application::get().getTime().getDeltaSeconds();

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<AnimationComponent>()) {
            auto animation = entity->getComponent<AnimationComponent>();
            auto velocity = entity->getComponent<VelocityComponent>();

            Animation &current = animation->getCurrent();

            animation->frameElapsedTime += time;
            if (animation->frameElapsedTime > current.frameTime) {
                animation->frameElapsedTime -= current.frameTime;
                animation->frameIndex++;
            }

            if (animation->frameIndex == current.framesNumber) {
                animation->frameIndex = 0;
            }
        }
    }
}

} // namespace Engine