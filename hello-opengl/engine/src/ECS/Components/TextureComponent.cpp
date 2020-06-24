#include "TextureComponent.hpp"

namespace Engine {

static std::vector<float> getVertices(const Rect &source) {
    float x0 = source.x;
    float y0 = source.y;
    float x1 = x0 + source.w;
    float y1 = source.y + source.h;

    return {
        1.0,  -1.0, 0.0, x1, y1,

        1.0,  1.0,  0.0, x1, y0,

        -1.0, 1.0,  0.0, x0, y0,

        -1.0, -1.0, 0.0, x0, y1,
    };
}

TextureComponent::TextureComponent(const std::string &name, const Rect &source,
                                   int width, int height, float alpha)
    : name(name), source(source), width(width), height(height), alpha(alpha) {
    vertexArray.reset(Engine::VertexArray::create());
    vertexArray->bind();

    std::vector<float> vertices = getVertices(source);
    std::vector<uint32_t> indexes = {0, 1, 2, 0, 2, 3};

    vertexBuffer.reset(Engine::VertexBuffer::create(vertices));
    indexBuffer.reset(Engine::IndexBuffer::create(indexes));

    Engine::BufferLayout layout = {
        {Engine::ShaderDataType::Float3, "a_position"},
        {Engine::ShaderDataType::Float2, "a_texCoord"},
    };

    vertexBuffer->setLayout(layout);
    vertexArray->addVertexBuffer(vertexBuffer);
    vertexArray->setIndexBuffer(indexBuffer);

    vertexArray->unbind();
}

void TextureComponent::update() {
    vertexArray->bind();
    vertexBuffer->setVertices(getVertices(source));
    vertexBuffer->bind();
    vertexArray->unbind();
}

} // namespace Engine