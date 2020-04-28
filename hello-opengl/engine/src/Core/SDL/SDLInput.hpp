#pragma once

#include "Input.hpp"
#include <SDL2/SDL.h>

namespace Engine {

class SDLInput : public Input {
  public:
    virtual void update() override;
    virtual bool IsKeyPressed(KeyCode key) override;
};

} // namespace Engine
