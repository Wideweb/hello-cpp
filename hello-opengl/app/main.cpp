#include "Application.hpp"
#include "EntryPoint.hpp"

const std::string vertexShader = R"(#version 330 core
                                    layout (location = 0) in vec3 position;
                                    layout (location = 1) in vec3 color;

                                    uniform vec2 mousePos;
                                    uniform float radius;

                                    out vec3 vColor;
                                    
                                    void main()
                                    {
                                        gl_Position = vec4(position, 1.0f);
                                        vColor = color;
                                    }
                                    )";

const std::string fragmentShader = R"(#version 330 core
                                    layout (location = 0) in vec3 position;
                                    layout (location = 1) in vec3 color;

                                    uniform vec2 mousePos;
                                    uniform float radius;

                                    out vec3 vColor;
                                    
                                    void main()
                                    {
                                        gl_Position = vec4(position, 1.0f);
                                        vColor = color;
                                    }
                                    )";

class MyLayer : public Engine::Layer {
  private:
    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::VertexBuffer> m_VertexBuffer;
    std::shared_ptr<Engine::IndexBuffer> m_IndexBuffer;
    std::shared_ptr<Engine::Shader> m_Shader;

    const float m_TileSize = 10.0f;

  public:
    virtual void onAttach() override {
        std::vector<float> vertices;
        std::vector<uint32_t> indexes;

        const float tilesNumberX = 640 / m_TileSize + 1;
        const float tilesNumberY = 420 / m_TileSize + 1;

        for (float i = 0; i < tilesNumberY; i++) {
            for (float j = 0; j < tilesNumberX; j++) {
                vertices.push_back(j * m_TileSize / 640 * 2 - 1); // x
                vertices.push_back(i * m_TileSize / 420 * 2 - 1); // y
                vertices.push_back(0.0);                          // z
                vertices.push_back(0.0);                          // r
                vertices.push_back(0.0);                          // g
                vertices.push_back(0.0);                          // b
            }
        }

        for (float i = 0; i < tilesNumberY - 1; i++) {
            for (float j = 0; j < tilesNumberX - 1; j++) {
                indexes.push_back(i * tilesNumberX + j);
                indexes.push_back(i * tilesNumberX + j + 1);

                indexes.push_back(i * tilesNumberX + j);
                indexes.push_back((i + 1) * tilesNumberX + j);
            }
        }

        m_VertexArray.reset(Engine::VertexArray::create());
        m_VertexBuffer.reset(Engine::VertexBuffer::create(vertices));
        m_IndexBuffer.reset(Engine::IndexBuffer::create(indexes));
        m_Shader.reset(Engine::Shader::create(vertexShader, fragmentShader));

        Engine::BufferLayout layout = {
            {Engine::ShaderDataType::Float3, "a_position"},
            {Engine::ShaderDataType::Float3, "a_color"},
        };

        m_VertexBuffer->setLayout(layout);
        m_VertexArray->addVertexBuffer(m_VertexBuffer);
        m_VertexArray->setIndexBuffer(m_IndexBuffer);
    }

    virtual void onRender() override {
        auto &render = Engine::Application::get().getRender();
        render.drawLines(m_Shader, m_VertexArray);
    }

    virtual void onMouseEvent(Engine::MouseEvent &e) override {
        if (e.type == Engine::EventType::MouseMoved) {
            float x = e.x;
            float y = e.y;
            float radius = 100;

            // m_Shader->setUniforms("mousePos", x, y);
            // m_Shader->setUniforms("radius", radius);
        }
    }
};

class MyApp : public Engine::Application {
  public:
    MyApp() {}

    virtual ~MyApp() {}
};

Engine::Application *Engine::createApplication() { return new MyApp(); }
