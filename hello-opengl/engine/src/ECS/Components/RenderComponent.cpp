#include "RenderComponent.hpp"

namespace Engine {

RenderComponent::RenderComponent(int width, int height, Vec3 color)
    : width(width), height(height), m_Color(color) {
    std::vector<float> vertices = {
        -1.0, -1.0, 0.0, color.x, color.y, color.z,

        -1.0, 1.0,  0.0, color.x, color.y, color.z,

        1.0,  -1.0, 0.0, color.x, color.y, color.z,

        1.0,  1.0,  0.0, color.x, color.y, color.z,
    };

    std::vector<uint32_t> indexes = {0, 1, 2, 1, 3, 2};

    init(vertices, indexes, width, height);
}

void RenderComponent::init(std::vector<float> &vertices,
                           std::vector<uint32_t> &indexes, int width,
                           int height) {
    vertexArray.reset(VertexArray::create());
    vertexArray->bind();

    vertexBuffer.reset(VertexBuffer::create(vertices));
    indexBuffer.reset(IndexBuffer::create(indexes));

    BufferLayout layout = {
        {ShaderDataType::Float3, "a_position"},
        {ShaderDataType::Float3, "a_color"},
    };

    vertexBuffer->setLayout(layout);
    vertexArray->addVertexBuffer(vertexBuffer);
    vertexArray->setIndexBuffer(indexBuffer);

    vertexArray->unbind();
}

} // namespace Engine