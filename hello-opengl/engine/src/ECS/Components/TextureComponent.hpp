#pragma once

#include "Buffer.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include <string>

namespace Engine {

class TextureComponent : public Component {
  public:
    int width;
    int height;
    float alpha;

    std::string name;
    Rect source;

    std::shared_ptr<Engine::VertexArray> vertexArray;
    std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
    std::shared_ptr<Engine::IndexBuffer> indexBuffer;

    TextureComponent(const std::string &name, const Rect &source, int width,
                     int height, float alpha);

    void update();

    virtual void serialize(std::ostringstream &out) override {
        out << "texture ";
        out << name << " ";
        out << source << " ";
        out << width << " ";
        out << height << " ";
        out << alpha;
        out << std::endl;
    }
};

} // namespace Engine