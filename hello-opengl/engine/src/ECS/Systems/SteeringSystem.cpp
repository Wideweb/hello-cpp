#include "SteeringSystem.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"
#include "SteeringComponent.hpp"
#include "TextureComponent.hpp"
#include "VelocityComponent.hpp"

#include <cmath>

namespace Engine {

void SteeringSystem ::exec(EntityManager &entities) {
    auto &app = Application::get();

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<SteeringComponent>()) {
            auto steering = entity->getComponent<SteeringComponent>();
            auto location = entity->getComponent<LocationComponent>();
            auto velocity = entity->getComponent<VelocityComponent>();
            auto target = entities.get(steering->target);
            auto targetLocation = target->getComponent<LocationComponent>();

            float direction = targetLocation->x - location->x;
            float distance = std::abs(direction);

            if (distance < 10) {
                velocity->x = 0;
                continue;
            }

            int sign = direction > 0 ? 1 : -1;
            velocity->x = sign * velocity->xMax;

            auto texture = entity->getComponent<TextureComponent>();
            texture->flip = direction < 0 ? Flip::Y : Flip::None;
        }
    }
}

} // namespace Engine
