#include "Application.hpp"
#include "EntryPoint.hpp"

const std::string vertexShader = R"(#version 330 core
                                    layout (location = 0) in vec3 a_position;
                                    layout (location = 1) in vec3 a_color;

                                    uniform vec2 mousePos;
                                    uniform float radius;
                                    uniform float ratio;

                                    out vec3 v_color;
                                    out vec3 v_position;
                                    
                                    void main()
                                    {
                                      vec3 v_mouse = vec3(mousePos, 0.0f);
                                      vec3 fixed_position = a_position * vec3(1, ratio, 1);
                                      float dist = distance(fixed_position, v_mouse);

                                      if (dist < radius) {
                                        float t = 1 - dist / radius;
                                        vec3 direction = normalize(fixed_position - v_mouse);
                                        vec3 offset = direction * t * 0.05;
                                        v_position = a_position + offset;
                                      } else {
                                        v_position = a_position;
                                      }

                                      v_color = a_color;
                                      gl_Position = vec4(v_position, 1.0f);
                                    }
                                    )";

const std::string fragmentShader = R"(#version 330 core
                                    in vec3 v_color;
                                    in vec3 v_position;
                                    
                                    uniform vec2 mousePos;
                                    uniform float radius;
                                    uniform float ratio;

                                    out vec3 vColor;
                                    
                                    void main()
                                    {
                                      vec3 color = v_color;
                                      vec3 v_mouse = vec3(mousePos, 0.0f);
                                      vec3 fixed_position = v_position * vec3(1, ratio, 1);
                                      float dist = distance(fixed_position, v_mouse);

                                      if (dist < radius) {
                                        float t = (dist / radius);
                                        color = color * t;
                                        color.x = color.x + (1 - t);
                                      }

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
                vertices.push_back(1.0);                          // g
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
        m_VertexArray->bind();

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
        render.setClearColor(0.0, 0.0, 0.0, 1.0);
        render.clear();
        render.drawLines(m_Shader, m_VertexArray);
    }

    virtual void onMouseEvent(Engine::MouseEvent &e) override {
        if (e.type == Engine::EventType::MouseMoved) {
            float x = (e.x / 640) * 2 - 1.0;
            float y = (e.y / -420) * 2 + 1.0;
            float radius = 0.3f;
            float ratio = 420.0f / 640.0f;

            m_Shader->SetFloat2("mousePos", x, y);
            m_Shader->SetFloat("radius", radius);
            m_Shader->SetFloat("ratio", ratio);
        }
    }
};

class MyApp : public Engine::Application {
  public:
    MyApp() { addLayer(new MyLayer()); }

    virtual ~MyApp() {}
};

Engine::Application *Engine::createApplication() { return new MyApp(); }
