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
            float width = static_cast<float>(app.getWindow().getWidth());
            app.getCamera().setPosition(location->x - width / 4, 0);
        }
    }
}

} // namespace Engine
