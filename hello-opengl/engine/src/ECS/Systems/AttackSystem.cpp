#include "AttackSystem.hpp"
#include "AABBOverlap.hpp"
#include "Application.hpp"
#include "AttackComponent.hpp"
#include "CollisionComponent.hpp"
#include "DieComponent.hpp"
#include "DirectionComponent.hpp"
#include "EnemyComponent.hpp"
#include "GroundCollisionComponent.hpp"
#include "GroupComponent.hpp"
#include "LocationComponent.hpp"
#include "VelocityComponent.hpp"
#include <cmath>

namespace Engine {

void AttackSystem::exec(EntityManager &entities) {
    auto &app = Application::get();
    auto &eventHandler = app.getEventHandler();

    auto entitiesWithAttack = entities.getByComponent<AttackComponent>();
    auto entitiesWithGroup = entities.getByComponent<GroupComponent>();

    for (auto entity : entitiesWithAttack) {
        auto die = entity->getComponent<DieComponent>();
        if (die && die->isActive) {
            continue;
        }

        auto attack = entity->getComponent<AttackComponent>();
        auto location = entity->getComponent<LocationComponent>();
        auto dir = entity->getComponent<DirectionComponent>();
        auto group = entity->getComponent<GroupComponent>();

        std::vector<Vec2> vertices;
        Vec2 move(location->x, location->y);

        std::transform(attack->vertices.begin(), attack->vertices.end(),
                       std::back_inserter(vertices),
                       [&](Vec2 &v) { return Vec2(v.x * dir->x, v.y) + move; });

        AABB entityAABB(vertices);

        for (auto entity_ : entitiesWithGroup) {
            auto die_ = entity_->getComponent<DieComponent>();
            if (die_ && die_->isActive) {
                continue;
            }

            auto group_ = entity_->getComponent<GroupComponent>();
            if (group->group == group_->group) {
                continue;
            }

            auto location_ = entity_->getComponent<LocationComponent>();
            auto collision_ = entity_->getComponent<CollisionComponent>();

            std::vector<Vec2> vertices_;
            Vec2 move_(location_->x, location_->y);

            std::transform(collision_->vertices.begin(),
                           collision_->vertices.end(),
                           std::back_inserter(vertices_),
                           [&](Vec2 &v) { return Vec2(v.x, v.y) + move_; });

            AABB entityAABB_(vertices_);

            if (AABBOverlap::test(entityAABB_, entityAABB)) {
                if (!die_) {
                    entity_->addComponent<DieComponent>();
                } else {
                    die_->isActive = true;
                }
            }
        }
    }
}

} // namespace Engine
