#pragma once

#include "Math.hpp"
#include <string>
#include <vector>

namespace Engine {

struct CollisionShape {
    std::string name;
    std::vector<Vec2> vertices;
    bool isStatic;

    CollisionShape() {}
    CollisionShape(const std::string &name, const std::vector<Vec2> &vertices,
                   bool isStatic)
        : name(name), vertices(vertices), isStatic(isStatic) {}
};

} // namespace Engine