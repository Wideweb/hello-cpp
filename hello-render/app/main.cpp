#include <cmath>
#include <iostream>

#include "Engine.hpp"

class myGfxProgram : public Engine::GfxProgram {
  private:
    float m_MouseX;
    float m_MouseY;
    float m_Radius;

  public:
    void setUniforms(const Engine::Uniforms &uniforms) override {
        m_MouseX = uniforms.f0;
        m_MouseY = uniforms.f1;
        m_Radius = uniforms.f2;
    }

    Engine::Vertex vertexShader(const Engine::Vertex &vertex) override {
        Engine::Vertex out;

        float dx = m_MouseX - vertex.f0;
        float dy = m_MouseY - vertex.f1;
        float angle = std::atan2(dy, dx);
        float t = 1 - (dx * dx + dy * dy) / (m_Radius * m_Radius);

        if (dx * dx + dy * dy < m_Radius * m_Radius) {
            out.f0 = vertex.f0 - m_Radius / 4 * t * cos(angle);
            out.f1 = vertex.f1 - m_Radius / 4 * t * sin(angle);
        } else {
            out.f0 = vertex.f0;
            out.f1 = vertex.f1;
        }

        out.f2 = vertex.f2;
        out.f3 = vertex.f3;
        out.f4 = vertex.f4;

        return out;
    }

    Color fragmentShader(const Engine::Vertex &vertex) override {
        float dx = m_MouseX - vertex.f0;
        float dy = m_MouseY - vertex.f1;
        float t = (dx * dx + dy * dy) / (m_Radius * m_Radius);

        uint8_t r = static_cast<uint8_t>(vertex.f2);
        uint8_t g = static_cast<uint8_t>(vertex.f3);
        uint8_t b = static_cast<uint8_t>(vertex.f4);

        if (dx * dx + dy * dy < m_Radius * m_Radius) {
            r = r * t + 255 * (1 - t);
            g = g * t;
            b = b * t;
        }

        return {r, g, b};
    }
};

class myApp : public Engine::Application {
  private:
    std::vector<Engine::Vertex> m_Vertexes;
    std::vector<int> m_Indexes;
    myGfxProgram m_Program;

    const float m_TileSize = 10.0f;

  public:
    myApp() {
        const float tilesNumberX = width / m_TileSize + 1;
        const float tilesNumberY = height / m_TileSize + 1;

        for (int i = 0; i < tilesNumberY; i++) {
            for (int j = 0; j < tilesNumberX; j++) {
                m_Vertexes.push_back(
                    {j * m_TileSize, i * m_TileSize, 0.0, 255.0, 0.0});
            }
        }

        for (int i = 0; i < tilesNumberY - 1; i++) {
            for (int j = 0; j < tilesNumberX - 1; j++) {
                m_Indexes.push_back(i * tilesNumberX + j);
                m_Indexes.push_back(i * tilesNumberX + j);
                m_Indexes.push_back(i * tilesNumberX + j + 1);

                m_Indexes.push_back(i * tilesNumberX + j);
                m_Indexes.push_back(i * tilesNumberX + j);
                m_Indexes.push_back((i + 1) * tilesNumberX + j);
            }
        }

        m_Render->setProgram(m_Program);
    }

    void render() override {
        m_Render->clear({0, 0, 0});
        m_Render->drawTriangles(m_Vertexes, m_Indexes);
    }

    void onMouseEvent(Engine::MouseEvent &e) override {
        if (e.type == Engine::EventType::MouseMoved) {
            float x = e.x;
            float y = e.y;
            float radius = 100;
            m_Program.setUniforms({x, y, radius});
        }
    }

    ~myApp() {}
};

int main(int argc, const char *argv[]) {
    auto app = new myApp();
    app->run();
    delete app;

    return 0;
}
