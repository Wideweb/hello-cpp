#include "ControlSystem.hpp"
#include "Application.hpp"
#include "KeyboardControlComponent.hpp"
#include "LocationComponent.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

void ControlSystem::exec(EntityManager &entities) {
    auto &input = Application::get().getInput();

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<KeyboardControlComponent>()) {
            auto keyboard = entity->getComponent<KeyboardControlComponent>();
            auto velocity = entity->getComponent<VelocityComponent>();
            auto location = entity->getComponent<LocationComponent>();

            if (input.IsKeyPressed(keyboard->leftKey)) {
                velocity->x = -2;
                location->direction = Direction::Left;
            } else if (input.IsKeyPressed(keyboard->rightKey)) {
                velocity->x = 2;
                location->direction = Direction::Right;
            } else {
                velocity->x = 0;
            }

            if (input.IsKeyPressed(keyboard->upKey)) {
                velocity->y = 4;
            }
        }
    }
}

} // namespace Engine
