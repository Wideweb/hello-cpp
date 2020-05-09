#include "TextureComponent.hpp"

namespace Engine {

TextureComponent::TextureComponent(const std::string &name,
                                   std::vector<float> &vertices,
                                   std::vector<uint32_t> &indexes,
                                   std::shared_ptr<Engine::Shader> shader,
                                   int width, int height, Flip flip)
    : name(name), shader(shader), width(width), height(height), flip(flip) {
    vertexArray.reset(Engine::VertexArray::create());
    vertexArray->bind();

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

} // namespace Engine