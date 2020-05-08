#pragma once

#include "Math.hpp"
#include <vector>

namespace Engine {

struct AABB {
    Vec2 min;
    Vec2 max;

    AABB() {}
    AABB(const std::vector<Vec2> &vertices) {
        std::vector<float> x;
        std::transform(vertices.begin(), vertices.end(), std::back_inserter(x),
                       [](Vec2 v) { return v.x; });

        std::vector<float> y;
        std::transform(vertices.begin(), vertices.end(), std::back_inserter(y),
                       [](Vec2 v) { return v.y; });

        max.x = *std::max_element(x.begin(), x.end());
        max.y = *std::max_element(y.begin(), y.end());

        min.x = *std::min_element(x.begin(), x.end());
        min.y = *std::min_element(y.begin(), y.end());
    }
};

} // namespace Engine
