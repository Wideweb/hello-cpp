#pragma once

#include "Entity.hpp"
#include "Math.hpp"
#include <string>
#include <memory>

namespace Engine {

struct BeginCollisionEvent {
    std::string first;
    std::string second;
};

struct EndCollisionEvent {
    std::string first;
    std::string second;
};

class CollisionComponent : public Component {
  public:
    std::vector<Vec2> vertices;
    std::shared_ptr<Entity> entity;

    CollisionComponent(float width, float height) {
        float wHalf = width / 2;
        float hHalf = height / 2;

        vertices.emplace_back(-wHalf, -hHalf);
        vertices.emplace_back(-wHalf, hHalf);
        vertices.emplace_back(wHalf, hHalf);
        vertices.emplace_back(wHalf, -hHalf);
    }

    CollisionComponent(const std::vector<Vec2> &vertices)
        : vertices(vertices) {}
};

} // namespace Engine