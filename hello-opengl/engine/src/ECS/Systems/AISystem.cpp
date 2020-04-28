#include "AISystem.hpp"
#include "AIComponent.hpp"
#include "Application.hpp"

namespace Engine {

void AISystem::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    auto &app = Application::get();

    for (auto entity : entities) {
        if (entity->hasComponent<AIComponent>()) {
            auto ai = entity->getComponent<AIComponent>();
            ai->tree->update();
        }
    }
}

} // namespace Engine
