#include "CameraSystem.hpp"
#include "Application.hpp"
#include "CameraComponent.hpp"
#include "LocationComponent.hpp"

namespace Engine {

void CameraSystem::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    auto &app = Application::get();

    for (auto entity : entities) {
        if (entity->hasComponent<CameraComponent>()) {
            auto c_location = entity->getComponent<LocationComponent>();
            auto c_camera = entity->getComponent<CameraComponent>();

            float width = static_cast<float>(app.getWindow().getWidth());
            int newPos = c_location->x + c_camera->offset;

            if (newPos > c_camera->leftBound &&
                newPos + width < c_camera->rightBound) {
                app.getCamera().setPosition(newPos, 0);
            }
        }
    }
}

} // namespace Engine
