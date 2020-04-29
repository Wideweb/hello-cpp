#include "ControlSystem.hpp"
#include "Application.hpp"
#include "KeyboardControlComponent.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

void ControlSystem::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    auto &input = Application::get().getInput();

    for (auto entity : entities) {
        if (entity->hasComponent<KeyboardControlComponent>()) {
            auto keyboard = entity->getComponent<KeyboardControlComponent>();
            auto velocity = entity->getComponent<VelocityComponent>();

            if (input.IsKeyPressed(keyboard->leftKey)) {
                velocity->x = -3;
            } else if (input.IsKeyPressed(keyboard->rightKey)) {
                velocity->x = 3;
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
