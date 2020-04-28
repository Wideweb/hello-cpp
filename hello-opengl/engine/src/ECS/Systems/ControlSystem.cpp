#include "ControlSystem.hpp"
#include "KeyboardControlComponent.hpp"

namespace Engine {

void ControlSystem::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    for (auto entity : entities) {
        if (entity->hasComponent<KeyboardControlComponent>()) {
        }
    }
}

} // namespace Engine
