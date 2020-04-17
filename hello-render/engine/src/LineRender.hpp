#pragma once

#include "Canvas.hpp"

namespace Engine {

class LineRender : IRender {
  private:
    Canvas &buffer;

  public:
    LineRender(Canvas &buffer);
    void clear(Color color) override;
    void setPixel(Position point, Color color) override;
    void drawLine(Position from, Position to, Color color);
};

} // namespace Engine
