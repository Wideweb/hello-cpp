#pragma once

#include "Buffer.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include <string>

namespace Engine {

enum class Flip { None = 0, Y = 1, X = 2 };

class TextureComponent : public Component {
  public:
    int width;
    int height;

    std::string name;
    Rect source;
    Flip flip;

    std::shared_ptr<Engine::VertexArray> vertexArray;
    std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
    std::shared_ptr<Engine::IndexBuffer> indexBuffer;
    std::shared_ptr<Engine::Shader> shader;

    TextureComponent(const std::string &name, const Rect &source, int width,
                     int height, std::shared_ptr<Engine::Shader> shader);
};

} // namespace Engine