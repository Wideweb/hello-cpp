#include "CollisionSystem.hpp"
#include "Application.hpp"
#include "CollisionComponent.hpp"
#include "LocationComponent.hpp"
#include "ObstacleComponent.hpp"
#include "SlopeComponent.hpp"
#include "VelocityComponent.hpp"
#include <cmath>

namespace Engine {

void CollisionSystem::exec(std::vector<std::shared_ptr<Entity>> &entities) {
    auto &app = Application::get();

    for (auto entity : entities) {
        if (entity->hasComponent<CollisionComponent>()) {
            auto entitylocation = entity->getComponent<LocationComponent>();
            auto entityCollider = entity->getComponent<CollisionComponent>();

            if (entity->hasComponent<ObstacleComponent>()) {
                continue;
            }

            auto entityVelocity = entity->getComponent<VelocityComponent>();

            for (auto obstacle : entities) {
                if (!obstacle->hasComponent<ObstacleComponent>()) {
                    continue;
                }

                auto obstacleCollider =
                    obstacle->getComponent<CollisionComponent>();
                auto obstacleLocation =
                    obstacle->getComponent<LocationComponent>();
                auto obstacleSlope = obstacle->getComponent<SlopeComponent>();

                float entityWidth = entityCollider->width;
                float entityHeight = entityCollider->height;
                float entityX = entitylocation->x - entityWidth / 2;
                float entityY = entitylocation->y - entityHeight / 2;
                float nextEntityX = entityX + entityVelocity->x;
                float nextEntityY = entityY + entityVelocity->y;

                float obstacleWidth = obstacleCollider->width;
                float obstacleHeight = obstacleCollider->height;
                float obstacleX = obstacleLocation->x - obstacleWidth / 2;
                float obstacleY = obstacleLocation->y - obstacleHeight / 2;
                float nextObstacleX = obstacleX;
                float nextObstacleY = obstacleY;

                if (obstacle->hasComponent<VelocityComponent>()) {
                    auto obstacleVelocity =
                        obstacle->getComponent<VelocityComponent>();
                    nextObstacleX += obstacleVelocity->x;
                    nextObstacleY += obstacleVelocity->y;
                }

                const bool hasCollision =
                    (nextEntityX <= nextObstacleX + obstacleWidth) &&
                    (nextEntityX + entityWidth >= nextObstacleX) &&
                    (nextEntityY <= nextObstacleY + obstacleHeight) &&
                    (nextEntityY + entityWidth >= nextObstacleY);

                if (!hasCollision) {
                    continue;
                }

                const auto toTopSide = [&]() {
                    entityVelocity->y = 0;
                    entitylocation->y =
                        nextObstacleY + obstacleHeight + entityHeight / 2;
                };

                const auto headToBottomSide = [&]() {
                    entityVelocity->y = 0;
                    entitylocation->y = nextObstacleY - entityHeight / 2;
                };

                const auto toBottomSide = [&]() {
                    entityVelocity->y = 0;
                    entitylocation->y = nextObstacleY + entityHeight / 2;
                };

                const auto toLeftSide = [&]() {
                    entityVelocity->x = 0;
                    entitylocation->x = nextObstacleX - entityWidth / 2;
                };

                const auto toRightSide = [&]() {
                    entityVelocity->x = 0;
                    entitylocation->x =
                        nextObstacleX + obstacleWidth + entityWidth / 2;
                };

                const bool fromUp = entityY + 1 >= obstacleY + obstacleHeight;
                const bool fromBottom = entityY + entityHeight <= obstacleY + 1;
                const bool fromLeft = entityX + entityWidth <= obstacleX;
                const bool fromRight = entityX >= obstacleX + obstacleWidth;

                if (!obstacleSlope) {
                    if (fromUp) {
                        toTopSide();
                    } else if (fromBottom) {
                        headToBottomSide();
                    } else if (fromLeft) {
                        toLeftSide();
                    } else if (fromRight) {
                        toRightSide();
                    }

                    continue;
                }

                if (obstacleSlope->right) {
                    if (fromRight && !fromUp) {
                        toRightSide();
                        continue;
                    }

                    float t = (nextEntityX + entityWidth - nextObstacleX) /
                              obstacleWidth;

                    if (t > 1 && t <= 1 + entityWidth / obstacleWidth) {
                        t = 1;
                    }

                    if (t < 0 || t > 1) {
                        continue;
                    }

                    const float y = nextObstacleY + t * obstacleHeight;

                    if (nextEntityY < y) {
                        entitylocation->y = y + entityHeight / 2;
                        entityVelocity->y = 0;
                    }
                }

                if (obstacleSlope->left) {
                    if (fromLeft && !fromUp) {
                        toLeftSide();
                        continue;
                    }

                    float t = (nextEntityX - nextObstacleX) / obstacleWidth;

                    if (t < 0 && t > -entityWidth / obstacleWidth) {
                        t = 0;
                    }

                    if (t < 0 || t > 1) {
                        continue;
                    }

                    const float y = nextObstacleY + (1 - t) * obstacleHeight;

                    if (nextEntityY < y) {
                        entitylocation->y = y + entityHeight / 2;
                        entityVelocity->y = 0;
                    }
                }
            }
        }
    }
}

} // namespace Engine
