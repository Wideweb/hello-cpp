#include "MoveSystem.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

void MoveSystem ::exec(EntityManager &entities) {
    auto &app = Application::get();

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<VelocityComponent>()) {
            auto velocity = entity->getComponent<VelocityComponent>();
            auto location = entity->getComponent<LocationComponent>();

            location->x += velocity->x; // * app.getTime().getDeltaSeconds();
            location->y += velocity->y; // * app.getTime().getDeltaSeconds();
        }
    }
}

} // namespace Engine
