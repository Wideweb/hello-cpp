#include "BroadPhaseAlgorithm.hpp"
#include "AABB.hpp"

namespace Engine {

std::vector<OverlappingPair> BroadPhaseAlgorithm::computeOverlappingPairs(
    const std::vector<CollisionShape> &shapes) {
    std::vector<OverlappingPair> pairs;

    std::vector<AABB> aabbs;
    std::transform(
        shapes.begin(), shapes.end(), std::back_inserter(aabbs),
        [](const CollisionShape &shape) { return AABB(shape.vertices); });

    for (size_t i = 0; i < shapes.size() - 1; i++) {
        for (size_t j = i + 1; j < shapes.size(); j++) {
            if (shapes[i].isStatic && shapes[j].isStatic) {
                continue;
            }

            if (testAABBOverlap(aabbs[i], aabbs[j])) {
                if (shapes[i].isStatic) {
                    pairs.emplace_back(shapes[j], shapes[i]);
                } else {
                    pairs.emplace_back(shapes[i], shapes[j]);
                }
            }
        }
    }

    return pairs;
}

bool BroadPhaseAlgorithm::testAABBOverlap(AABB &a, AABB &b) {
    float d1x = b.min.x - a.max.x;
    float d1y = b.min.y - a.max.y;
    float d2x = a.min.x - b.max.x;
    float d2y = a.min.y - b.max.y;

    if (d1x > 0.0f || d1y > 0.0f)
        return false;

    if (d2x > 0.0f || d2y > 0.0f)
        return false;

    return true;
}

} // namespace Engine
