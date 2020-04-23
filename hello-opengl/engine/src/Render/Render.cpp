#include "Render.hpp"
#include "OpenGLRender.hpp"

namespace Engine {

Render *Render::create() { return new OpenGLRender(); }

} // namespace Engine
