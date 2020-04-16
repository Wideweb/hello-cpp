#include "TriangleRender.hpp"

namespace Engine {

TriangleRender::TriangleRender(Canvas &buffer) : LineRender(buffer) {}

void TriangleRender::drawTriangle(Pixels<3> points, Color color) {
    drawLine(points[0], points[1], color);
    drawLine(points[1], points[2], color);
    drawLine(points[2], points[0], color);
}

} // namespace Engine
