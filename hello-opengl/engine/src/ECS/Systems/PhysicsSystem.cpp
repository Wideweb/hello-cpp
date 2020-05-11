#include "PhysicsSystem.hpp"
#include "Application.hpp"
#include "RigitBodyComponent.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

void PhysicsSystem::exec(EntityManager &entities) {
    auto &app = Application::get();

    for (auto entity : entities.getAll()) {
        if (entity->hasComponent<RigitBodyComponent>()) {
            auto c_rigitBody = entity->getComponent<RigitBodyComponent>();
            auto c_velocity = entity->getComponent<VelocityComponent>();

            c_velocity->y -=
                c_rigitBody->weight; // * app.getTime().getDeltaSeconds();
        }
    }
}

} // namespace Engine
