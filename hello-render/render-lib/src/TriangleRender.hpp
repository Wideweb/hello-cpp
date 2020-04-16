#pragma once

#include "LineRender.hpp"
#include <vector>

namespace Engine {

class TriangleRender : public LineRender {
  public:
    TriangleRender(Canvas &buffer);
    void drawTriangle(Pixels<3> points, Color color);
};

} // namespace Engine
