#include "AISystem.hpp"
#include "AIComponent.hpp"
#include "Application.hpp"

namespace Engine {

void AISystem::exec(EntityManager &entities) {
    auto &app = Application::get();

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<AIComponent>()) {
            auto ai = entity->getComponent<AIComponent>();
            ai->tree->update();
        }
    }
}

} // namespace Engine
