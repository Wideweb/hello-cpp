#include "CameraSystem.hpp"
#include "Application.hpp"
#include "CameraComponent.hpp"
#include "LocationComponent.hpp"

namespace Engine {

void CameraSystem::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    auto &app = Application::get();

    for (auto entity : entities) {
        if (entity->hasComponent<CameraComponent>()) {
            auto location = entity->getComponent<LocationComponent>();
            app.getCamera().setPosition(location->x - 600 / 4, 0);
        }
    }
}

} // namespace Engine
