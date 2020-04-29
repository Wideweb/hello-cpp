#pragma once

#include "Entity.hpp"
#include "Input.hpp"

namespace Engine {

class KeyboardControlComponent : public Component {
  public:
    KeyCode upKey;
    KeyCode rightKey;
    KeyCode leftKey;

    KeyboardControlComponent(KeyCode upKey, KeyCode rightKey, KeyCode leftKey)
        : upKey(upKey), rightKey(rightKey), leftKey(leftKey) {}
};

} // namespace Engine