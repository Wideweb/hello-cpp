#pragma once

#include <string>
#include <vector>

namespace Engine {

enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4 };

static uint32_t ShaderDataTypeSize(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    default:
        return 0;
    }
};

struct BufferElement {
    std::string name;
    ShaderDataType type;
    uint32_t size;
    uint32_t offset;

    BufferElement() {}

    BufferElement(ShaderDataType type, const std::string name)
        : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0) {}

    uint8_t getElementCount() const {
        switch (type) {
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        default:
            return 0;
        }
    }
};

class BufferLayout {
  private:
    std::vector<BufferElement> m_Elements;
    uint32_t m_Stride;

  public:
    BufferLayout() {}

    BufferLayout(const std::initializer_list<BufferElement> &elements)
        : m_Elements(elements) {
        uint32_t offset = 0;
        for (auto &element : m_Elements) {
            element.offset = offset;
            offset += element.size;
        }
        m_Stride = offset;
    }

    uint32_t getStride() const { return m_Stride; }
    std::vector<BufferElement> &getElements() { return m_Elements; }
    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const {
        return m_Elements.begin();
    }
    std::vector<BufferElement>::const_iterator end() const {
        return m_Elements.end();
    }
};

class VertexBuffer {
  public:
    virtual ~VertexBuffer() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void setLayout(BufferLayout &layout) = 0;
    virtual const BufferLayout &getLayout() const = 0;

    virtual void setVertices(const std::vector<float> &vertices) = 0;

    static VertexBuffer *create(const std::vector<float> &vertices);
};

class IndexBuffer {
  public:
    virtual ~IndexBuffer() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual int32_t getCount() const = 0;

    static IndexBuffer *create(const std::vector<uint32_t> &indexes);
};

} // namespace Engine
