#include "LineRender.hpp"

namespace Engine {

LineRender::LineRender(Canvas &buffer) : buffer(buffer) {}

void LineRender::clear(Color color) {
    std::fill(buffer.begin(), buffer.end(), color);
}

void LineRender::setPixel(Position point, Color color) {
    if (point.x >= 0 && point.x < width && point.y >= 0 && point.y < height) {
        buffer[point.y * width + point.x] = color;
    }
}

void LineRender::drawLine(Position from, Position to, Color color) {
    auto byX = [&](int x0, int y0, int x1, int y1) {
        uint16_t dx = std::abs(x1 - x0);
        uint16_t dy = std::abs(y1 - y0);
        uint16_t error = 0;
        uint16_t derror = dy + 1;

        uint16_t y = y0;
        int diry = y1 > y0 ? 1 : -1;

        uint16_t fromX = x0;
        uint16_t toX = x1;

        if (x0 > x1) {
            fromX = x1;
            toX = x0;
            y = y1;
            diry *= -1;
        }

        for (uint16_t x = fromX; x <= toX; x += 1) {
            setPixel({x, y}, color);
            error += derror;
            if (error > dx + 1) {
                y += diry;
                error -= (dx + 1);
            }
        }
    };

    auto byY = [&](int x0, int y0, int x1, int y1) {
        uint16_t dx = std::abs(x1 - x0);
        uint16_t dy = std::abs(y1 - y0);
        uint16_t error = 0;
        uint16_t derror = dx + 1;

        uint16_t x = x0;
        int dirx = x1 > x0 ? 1 : -1;

        uint16_t fromY = y0;
        uint16_t toY = y1;

        if (y0 > y1) {
            fromY = y1;
            toY = y0;
            x = x1;
            dirx *= -1;
        }

        for (uint16_t y = fromY; y <= toY; y += 1) {
            setPixel({x, y}, color);
            error += derror;
            if (error > dy + 1) {
                x += dirx;
                error -= (dy + 1);
            }
        }
    };

    if (std::abs(to.x - from.x) > std::abs(to.y - from.y)) {
        byX(from.x, from.y, to.x, to.y);
    } else {
        byY(from.x, from.y, to.x, to.y);
    }
}

}