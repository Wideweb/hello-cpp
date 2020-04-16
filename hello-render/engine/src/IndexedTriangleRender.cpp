#include "IndexedTriangleRender.hpp"

namespace Engine {

void IndexedTriangleRender::drawTriangles(Pixels<3> vertexes,
                                          std::vector<int> indexes,
                                          Color color) {
    for (size_t i = 0; i < indexes.size(); i += 3) {

        drawTriangle({vertexes.at(indexes.at(i)),
                      vertexes.at(indexes.at(i + 1)),
                      vertexes.at(indexes.at(i + 2))},
                     color);
    }
}

}