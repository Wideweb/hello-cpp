#include "SDLInput.hpp"
#include <iostream>

namespace Engine {

static SDL_Scancode getSDLScancode(KeyCode code) {
    switch (code) {
    case KeyCode::Space:
        return SDL_SCANCODE_SPACE;
    case KeyCode::A:
        return SDL_SCANCODE_A;
    case KeyCode::D:
        return SDL_SCANCODE_D;
    case KeyCode::S:
        return SDL_SCANCODE_S;
    case KeyCode::W:
        return SDL_SCANCODE_W;
    case KeyCode::Escape:
        return SDL_SCANCODE_ESCAPE;
    default:
        return SDL_SCANCODE_UNKNOWN;
    }
}

void SDLInput::update() { SDL_PumpEvents(); }

bool SDLInput::IsKeyPressed(KeyCode key) {
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    return keystates[getSDLScancode(key)];
}

} // namespace Engine
