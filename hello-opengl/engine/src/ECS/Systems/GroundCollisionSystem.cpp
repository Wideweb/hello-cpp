#include "GroundCollisionSystem.hpp"
#include "Application.hpp"
#include "CollisionComponent.hpp"
#include "GroundCollisionComponent.hpp"
#include "GroundComponent.hpp"
#include "LocationComponent.hpp"
#include "ObstacleComponent.hpp"
#include "VelocityComponent.hpp"
#include <cmath>

namespace Engine {

void GroundCollisionSystem::exec(EntityManager &entities) {
    auto &app = Application::get();
    auto &eventHandler = app.getEventHandler();

    std::vector<CollisionShape> groundColliders;
    auto ground = entities.getByComponent<GroundComponent>();
    for (auto &entity : ground) {
        auto collision = entity->getComponent<CollisionComponent>();
        auto location = entity->getComponent<LocationComponent>();

        Vec2 move(location->x, location->y);

        std::vector<Vec2> vertices;
        std::transform(collision->vertices.begin(), collision->vertices.end(),
                       std::back_inserter(vertices),
                       [&](Vec2 &v) { return v + move; });

        groundColliders.emplace_back(entity->getName(), vertices, true);
    }

    for (auto &entity : entities.getAll()) {
        if (!entity->hasComponent<GroundCollisionComponent>()) {
            continue;
        }

        auto collision = entity->getComponent<GroundCollisionComponent>();
        auto location = entity->getComponent<LocationComponent>();
        auto velocity = entity->getComponent<VelocityComponent>();

        collision->entity = nullptr;

        Vec2 move(location->x, location->y);

        std::vector<Vec2> vertices;
        std::transform(collision->vertices.begin(), collision->vertices.end(),
                       std::back_inserter(vertices),
                       [&](Vec2 &v) { return v + move; });

        CollisionShape collider(entity->getName(), vertices, false);
        collision->onGround = false;
        for (auto &ground : groundColliders) {
            std::vector<CollisionShape> colliders = {collider, ground};
            auto results = m_CollisionDetection.detect(colliders);
            if (!results.empty()) {
                velocity->x = 0;
                velocity->y = 0;
                collision->onGround = true;
                break;
            }
        }
    }
}

} // namespace Engine
