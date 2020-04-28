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

class Input {
  public:
    virtual ~Input() = default;
    virtual void update(){};
    virtual bool IsKeyPressed(KeyCode key) = 0;

    static Input *create();
};

} // namespace Engine
