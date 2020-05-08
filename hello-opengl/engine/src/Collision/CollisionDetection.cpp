#include "CollisionDetection.hpp"

namespace Engine {

std::vector<CollisionResult>
CollisionDetection::detect(const std::vector<CollisionShape> &shapes) {
    std::vector<CollisionResult> result;

    std::vector<OverlappingPair> pairs =
        m_BroadPhase.computeOverlappingPairs(shapes);

    for (auto pair : pairs) {
        Vec2 mtv = m_NarrowPhase.collide(pair.shape1, pair.shape2);
        if (mtv.x != 0 || mtv.y != 0) {
            result.emplace_back(pair.shape1.name, pair.shape2.name, mtv);
        }
    }

    return result;
}

} // namespace Engine