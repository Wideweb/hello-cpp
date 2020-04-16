#pragma once

#include "GfxProgram.hpp"
#include "IndexedTriangleRender.hpp"

namespace Engine {

class InterpolatedTriangleRender : public IndexedTriangleRender {
  private:
    GfxProgram *m_Program;
    Vertex interpolate(Vertex v0, Vertex v1, float t);
    float interpolate(float from, float to, float t);
    bool isCollinear(Vertex v0, Vertex v1, Vertex v2);

  public:
    InterpolatedTriangleRender(Canvas &buffer)
        : IndexedTriangleRender(buffer) {}

    void setProgram(GfxProgram &program);

    void drawTriangles(std::vector<Vertex> vertexes, std::vector<int> indexes);

    std::vector<Vertex> rasterizeTriange(Vertex v0, Vertex v1, Vertex v2);
};

} // namespace Engine
