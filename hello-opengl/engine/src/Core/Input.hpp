#include "Math.hpp"

#pragma once

namespace Engine {

enum class KeyCode {
    None = 0,
    Space = 32,
    A = 65,
    D = 68,
    S = 83,
    W = 87,
    Escape = 256,
};

enum class MouseButton { None = 0, Left = 1, Right = 2, Middle = 3 };

class Input {
  public:
    virtual ~Input() = default;
    virtual void update(){};
    virtual bool IsKeyPressed(KeyCode key) = 0;
    virtual bool IsMousePressed(MouseButton button) = 0;
    virtual Vec2 GetMousePosition() = 0;

    static Input *create();
};

} // namespace Engine
