#include "VertexArray.hpp"
#include "OpenGLVertexArray.hpp"

namespace Engine {

VertexArray *VertexArray::create() { return new OpenGLVertexArray(); }

} // namespace Engine
