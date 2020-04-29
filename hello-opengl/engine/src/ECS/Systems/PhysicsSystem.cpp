#include "PhysicsSystem.hpp"
#include "Application.hpp"
#include "RigitBodyComponent.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

void PhysicsSystem::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    auto &app = Application::get();

    for (auto entity : entities) {
        if (entity->hasComponent<RigitBodyComponent>()) {
            auto c_rigitBody = entity->getComponent<RigitBodyComponent>();
            auto c_velocity = entity->getComponent<VelocityComponent>();

            c_velocity->y -= c_rigitBody->weight * app.getTime().getDelta();
        }
    }
}

} // namespace Engine
