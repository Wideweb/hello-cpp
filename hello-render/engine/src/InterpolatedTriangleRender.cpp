#include "InterpolatedTriangleRender.hpp"
#include <cmath>

namespace Engine {

void InterpolatedTriangleRender::setProgram(GfxProgram &program) {
    m_Program = &program;
}

void InterpolatedTriangleRender::drawTriangles(std::vector<Vertex> &vertexes,
                                               std::vector<int> &indexes) {
    for (size_t i = 0; i < indexes.size(); i += 3) {
        Vertex v0 = m_Program->vertexShader(vertexes.at(indexes.at(i)));
        Vertex v1 = m_Program->vertexShader(vertexes.at(indexes.at(i + 1)));
        Vertex v2 = m_Program->vertexShader(vertexes.at(indexes.at(i + 2)));

        auto triangle = rasterizeTriange(v0, v1, v2);

        for (auto &rasterized : triangle) {
            uint16_t x = std::round(rasterized.f0);
            uint16_t y = std::round(rasterized.f1);

            setPixel({x, y}, m_Program->fragmentShader(rasterized));
        }
    }
}

std::vector<Vertex> InterpolatedTriangleRender::rasterizeTriange(Vertex &v0,
                                                                 Vertex &v1,
                                                                 Vertex &v2) {
    std::vector<Vertex> out;

    auto degenerateTriangleByX = [&](Vertex &top, Vertex &middle,
                                     Vertex &bottom) {
        std::vector<Vertex> line = {top, middle, bottom};
        std::sort(line.begin(), line.end(), [&](Vertex first, Vertex second) {
            return first.f0 < second.f0;
        });

        Vertex from = line[0];
        Vertex to = line[2];

        for (float x = from.f0; x <= to.f0; x++) {
            out.push_back(
                interpolate(from, to, (x - from.f0) / (to.f0 - from.f0)));
        }
    };

    auto degenerateTriangleByY = [&](Vertex &top, Vertex &middle,
                                     Vertex &bottom) {
        std::vector<Vertex> line = {top, middle, bottom};
        std::sort(line.begin(), line.end(), [&](Vertex first, Vertex second) {
            return first.f1 < second.f1;
        });

        Vertex from = line[0];
        Vertex to = line[2];

        for (float y = from.f1; y <= to.f1; y++) {
            out.push_back(
                interpolate(from, to, (y - from.f1) / (to.f1 - from.f1)));
        }
    };

    auto horizontalUpwardTriangle = [&](Vertex &top, Vertex &middleLeft,
                                        Vertex &middleRight) {
        for (float y = 0; y <= middleLeft.f1 - top.f1; y++) {
            Vertex from =
                interpolate(middleLeft, top, y / (middleLeft.f1 - top.f1));
            Vertex to =
                interpolate(middleRight, top, y / (middleRight.f1 - top.f1));

            for (float x = from.f0; x <= to.f0; x++) {
                out.push_back(
                    interpolate(from, to, (x - from.f0) / (to.f0 - from.f0)));
            }
        }
    };

    auto horizontalDownwardTriangle = [&](Vertex &top, Vertex &middleLeft,
                                          Vertex &middleRight) {
        for (float y = 0; y <= top.f1 - middleLeft.f1; y++) {
            Vertex from =
                interpolate(middleLeft, top, y / (top.f1 - middleLeft.f1));
            Vertex to =
                interpolate(middleRight, top, y / (top.f1 - middleRight.f1));

            for (float x = from.f0; x <= to.f0; x++) {
                out.push_back(
                    interpolate(from, to, (x - from.f0) / (to.f0 - from.f0)));
            }
        }
    };

    if (isCollinear(v0, v1, v2)) {
        float minX = std::min({v0.f0, v1.f0, v2.f0});
        float maxX = std::max({v0.f0, v1.f0, v2.f0});

        float minY = std::min({v0.f1, v1.f1, v2.f1});
        float maxY = std::max({v0.f1, v1.f1, v2.f1});

        float dx = maxX - minX;
        float dy = maxY - minY;

        if (dx > dy) {
            degenerateTriangleByX(v0, v1, v2);
        } else {
            degenerateTriangleByY(v0, v1, v2);
        }

        return out;
    }

    std::vector<Vertex> vertexes = {v0, v1, v2};
    std::sort(
        vertexes.begin(), vertexes.end(),
        [&](Vertex &first, Vertex &second) { return first.f1 < second.f1; });

    Vertex top = vertexes[0];
    Vertex middle = vertexes[1];
    Vertex bottom = vertexes[2];

    if (middle.f1 == top.f1) {
        Vertex middeleLeft = middle.f0 < top.f0 ? middle : top;
        Vertex middleRight = middle.f0 < top.f0 ? top : middle;

        horizontalDownwardTriangle(bottom, middeleLeft, middleRight);
        return out;
    }

    if (middle.f1 == bottom.f1) {
        Vertex middeleLeft = middle.f0 < bottom.f0 ? middle : bottom;
        Vertex middleRight = middle.f0 < bottom.f0 ? bottom : middle;

        horizontalUpwardTriangle(top, middeleLeft, middleRight);
        return out;
    }

    Vertex middle2 = interpolate(
        bottom, top, (bottom.f1 - middle.f1) / (bottom.f1 - top.f1));

    Vertex middeleLeft = middle.f0 < middle2.f0 ? middle : middle2;
    Vertex middleRight = middle.f0 < middle2.f0 ? middle2 : middle;

    horizontalUpwardTriangle(top, middeleLeft, middleRight);
    horizontalDownwardTriangle(bottom, middeleLeft, middleRight);

    return out;
}

Vertex InterpolatedTriangleRender::interpolate(Vertex &v0, Vertex &v1,
                                               float t) {
    return {interpolate(v0.f0, v1.f0, t), interpolate(v0.f1, v1.f1, t),
            interpolate(v0.f2, v1.f2, t), interpolate(v0.f3, v1.f3, t),
            interpolate(v0.f4, v1.f4, t)};
}

float InterpolatedTriangleRender::interpolate(float from, float to, float t) {
    return from + (to - from) * t;
}

bool InterpolatedTriangleRender::isCollinear(Vertex &v0, Vertex &v1,
                                             Vertex &v2) {
    return (v1.f0 - v0.f0) * (v2.f1 - v0.f1) ==
           (v2.f0 - v0.f0) * (v1.f1 - v0.f1);
}

} // namespace Engine
