#include "SDLInput.hpp"
#include <iostream>

namespace Engine {

static SDL_KeyCode getSDLKeyCode(KeyCode code) {
    switch (code) {
    case KeyCode::Space:
        return SDLK_SPACE;
    case KeyCode::A:
        return SDLK_a;
    case KeyCode::D:
        return SDLK_d;
    case KeyCode::S:
        return SDLK_s;
    case KeyCode::W:
        return SDLK_w;
    case KeyCode::Escape:
        return SDLK_ESCAPE;
    default:
        return SDLK_UNKNOWN;
    }
}

void SDLInput::update() { SDL_PumpEvents(); }

bool SDLInput::IsKeyPressed(KeyCode key) {
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    return keystates[SDL_GetScancodeFromKey(getSDLKeyCode(key))];
}

} // namespace Engine
