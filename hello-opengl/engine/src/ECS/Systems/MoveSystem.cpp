#include "MoveSystem.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

void MoveSystem ::exec(EntityManager &entities) {
    auto &app = Application::get();

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<VelocityComponent>()) {
            auto c_velocity = entity->getComponent<VelocityComponent>();
            auto c_location = entity->getComponent<LocationComponent>();

            c_location->x += c_velocity->x * app.getTime().getDeltaSeconds();
            c_location->y += c_velocity->y * app.getTime().getDeltaSeconds();
        }
    }
}

} // namespace Engine
