#include "NarrowPhaseAlgorithm.hpp"
#include <algorithm>
#include <limits>
#include <numeric>

namespace Engine {

Vec2 NarrowPhaseAlgorithm::collide(const CollisionShape &shape1,
                                   const CollisionShape &shape2) {
    Vec2 mtv;
    float minOverlap = std::numeric_limits<float>::max();

    auto axis1 = getAxis(shape1.vertices);
    auto axis2 = getAxis(shape2.vertices);

    std::vector<Vec2> axis;

    axis.insert(axis.end(), axis1.begin(), axis1.end());
    axis.insert(axis.end(), axis2.begin(), axis2.end());

    for (size_t i = 0; i < axis.size(); i++) {
        std::vector<float> scalars1;
        std::vector<float> scalars2;

        for (auto corner : shape1.vertices) {
            scalars1.push_back(axis[i].dot(corner));
        }

        for (auto corner : shape2.vertices) {
            scalars2.push_back(axis[i].dot(corner));
        }

        float s1max = *std::max_element(scalars1.begin(), scalars1.end());
        float s1min = *std::min_element(scalars1.begin(), scalars1.end());

        float s2max = *std::max_element(scalars2.begin(), scalars2.end());
        float s2min = *std::min_element(scalars2.begin(), scalars2.end());

        if (s1min > s2max || s2min > s1max) {
            return Vec2(0, 0);
        }

        float overlap = s1max > s2max ? (s2max - s1min) : (s2min - s1max);
        if (minOverlap > std::abs(overlap)) {
            minOverlap = std::abs(overlap);
            mtv = axis[i] * overlap;
        }
    }

    return mtv;
}

std::vector<Vec2>
NarrowPhaseAlgorithm::getAxis(const std::vector<Vec2> &corners) {
    std::vector<Vec2> axis;
    for (size_t i = 0; i < corners.size() - 1; i++) {
        Vec2 v1 = corners[i];
        Vec2 v2 = corners[i + 1];
        Vec2 d = v2 - v1;
        axis.push_back(d.normalL().unit());
    }

    Vec2 v1 = corners.back();
    Vec2 v2 = corners.front();
    Vec2 d = v2 - v1;
    axis.push_back(d.normalL().unit());

    return axis;
}

} // namespace Engine
