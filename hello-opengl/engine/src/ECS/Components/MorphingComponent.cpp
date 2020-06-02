#include "MorphingComponent.hpp"

namespace Engine {

MorphingComponent::MorphingComponent(std::vector<float> &from,
                                     std::vector<float> &to,
                                     std::vector<uint32_t> &indexes,
                                     const std::string &shader, int width,
                                     int height)
    : shader(shader), width(width), height(height) {
    vertexArray.reset(Engine::VertexArray::create());
    vertexArray->bind();

    int batchSize = 6;
    int batchNumber = from.size() / batchSize;

    std::vector<float> vertices;
    for (size_t i = 0; i < batchNumber; i++) {
        vertices.insert(vertices.end(), from.begin() + i * batchSize,
                        from.begin() + (i + 1) * batchSize);
        vertices.insert(vertices.end(), to.begin() + i * batchSize,
                        to.begin() + (i + 1) * batchSize);
    }

    vertexBuffer.reset(Engine::VertexBuffer::create(vertices));
    indexBuffer.reset(Engine::IndexBuffer::create(indexes));

    Engine::BufferLayout layout = {
        {Engine::ShaderDataType::Float3, "from_position"},
        {Engine::ShaderDataType::Float3, "from_color"},
        {Engine::ShaderDataType::Float3, "to_position"},
        {Engine::ShaderDataType::Float3, "to_color"},
    };

    vertexBuffer->setLayout(layout);
    vertexArray->addVertexBuffer(vertexBuffer);
    vertexArray->setIndexBuffer(indexBuffer);

    vertexArray->unbind();
}

} // namespace Engine