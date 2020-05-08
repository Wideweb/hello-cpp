#include "CollisionSystem.hpp"
#include "Application.hpp"
#include "LocationComponent.hpp"
#include "ObstacleComponent.hpp"
#include <cmath>

namespace Engine {

void CollisionSystem::exec(EntityManager &entities) {
    auto &app = Application::get();
    auto eventHandler = app.getEventHandler();

    std::vector<CollisionShape> colliders;
    for (auto &entity : entities.getAll()) {

        if (!entity->hasComponent<CollisionComponent>()) {
            continue;
        }

        auto collision = entity->getComponent<CollisionComponent>();
        auto location = entity->getComponent<LocationComponent>();

        Vec2 move(location->x, location->y);

        if (entity->hasComponent<VelocityComponent>()) {
            auto velocity = entity->getComponent<VelocityComponent>();
            move = move + Vec2(velocity->x, velocity->y);
        }

        std::vector<Vec2> vertices;
        std::transform(collision->vertices.begin(), collision->vertices.end(),
                       std::back_inserter(vertices),
                       [&](Vec2 &v) { return v + move; });

        colliders.emplace_back(entity->getName(), vertices,
                               entity->hasComponent<ObstacleComponent>());
    }

    std::vector<CollisionResult> results =
        m_CollisionDetection.detect(colliders);

    for (auto &result : results) {
        auto entity = entities.get(result.shape1);
        auto location = entity->getComponent<LocationComponent>();
        auto velocity = entity->getComponent<VelocityComponent>();

        location->x -= result.mtv.x;
        location->y -= result.mtv.y;

        if (velocity->x * result.mtv.x < 0) {
            location->x += velocity->x;
            velocity->x = 0;
        }

        if (velocity->y * result.mtv.y > 0) {
            location->y += velocity->y;
            velocity->y = 0;
        }

        BeginCollisionEvent event;
        event.first = result.shape1;
        event.second = result.shape2;
        eventHandler.send<BeginCollisionEvent>(event);
    }

    // for (size_t i = 0; i < entitiesToCheck.size() - 1; i++) {
    //     auto thisEntity = entitiesToCheck[i];

    //     for (size_t j = i + 1; j < entitiesToCheck.size(); j++) {
    //         auto thatEntity = entitiesToCheck[j];

    //         CollisionResult collision =
    //             m_CollisionDetection.detect()
    //                 thisCollider.checkCollision(thatCollider);

    //         if (collision == CollisionResult::None) {
    //             EndCollisionEvent event;
    //             event.first = thatEntity->getName();
    //             event.second = thisEntity->getName();
    //             eventHandler.send<EndCollisionEvent>(event);
    //             continue;
    //         }

    //         BeginCollisionEvent event;
    //         event.first = thatEntity->getName();
    //         event.second = thisEntity->getName();
    //         eventHandler.send<BeginCollisionEvent>(event);
    //     }
    // }
}

} // namespace Engine
