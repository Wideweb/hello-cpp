#pragma once

#include "TriangleRender.hpp"
#include <vector>

namespace Engine {

class IndexedTriangleRender : public TriangleRender {
  public:
    IndexedTriangleRender(Canvas &buffer) : TriangleRender(buffer) {}

    void drawTriangles(Pixels<3> vertexes, std::vector<int> indexes,
                       Color color);
};

} // namespace Engine
