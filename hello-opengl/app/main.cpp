#include "AIComponent.hpp"
#include "Application.hpp"
#include "BlackboardManager.hpp"
#include "CameraComponent.hpp"
#include "CollisionComponent.hpp"
#include "EntryPoint.hpp"
#include "LocationComponent.hpp"
#include "MoveTask.hpp"
#include "ObstacleComponent.hpp"
#include "RenderComponent.hpp"
#include "RigitBodyComponent.hpp"
#include "SequenceTask.hpp"
#include "SlopeComponent.hpp"
#include "UntilFail.hpp"
#include "VelocityComponent.hpp"

const std::string vertexShader = R"(#version 330 core
                                    layout (location = 0) in vec3 a_position;
                                    layout (location = 1) in vec3 a_color;

                                    uniform mat4 MVP;

                                    out vec3 v_color;
                                    
                                    void main()
                                    {
                                      v_color = a_color;
                                      gl_Position = MVP * vec4(a_position, 1.0f);
                                    }
                                    )";

const std::string fragmentShader = R"(#version 330 core
                                    in vec3 v_color;

                                    out vec3 vColor;
                                    
                                    void main()
                                    {
                                      vColor = v_color;
                                    }
                                    )";

class MyLayer : public Engine::Layer {
  private:
    std::shared_ptr<Engine::Shader> m_Shader;
    std::shared_ptr<Engine::Entity> m_Player;
    std::shared_ptr<Engine::Entity> m_Lift;

  public:
    virtual void onAttach() override {
        m_Shader.reset(Engine::Shader::create(vertexShader, fragmentShader));

        std::vector<float> vertices = {
            -1.0, -1.0, 0.0, 0.0, 0.0, 1.0,

            -1.0, 1.0,  0.0, 0.0, 0.0, 1.0,

            1.0,  -1.0, 0.0, 0.0, 0.0, 1.0,
        };

        std::vector<uint32_t> indexes = {0, 1, 2};

        auto entity3 = addEntity("box");
        entity3->addComponent<Engine::LocationComponent>(400.0, 75.0, 0);
        entity3->addComponent<Engine::ObstacleComponent>();
        entity3->addComponent<Engine::SlopeComponent>(true);
        entity3->addComponent<Engine::CollisionComponent>(50, 50);
        entity3->addComponent<Engine::RenderComponent>(vertices, indexes,
                                                       m_Shader, 50, 50);

        vertices = {
            -1.0, -1.0, 0.0, 0.0, 0.0, 1.0,

            1.0,  1.0,  0.0, 0.0, 0.0, 1.0,

            1.0,  -1.0, 0.0, 0.0, 0.0, 1.0,
        };

        indexes = {0, 1, 2};

        auto entity5 = addEntity("box");
        entity5->addComponent<Engine::LocationComponent>(300.0, 75.0, 0);
        entity5->addComponent<Engine::ObstacleComponent>();
        entity5->addComponent<Engine::SlopeComponent>(false);
        entity5->addComponent<Engine::CollisionComponent>(50, 50);
        entity5->addComponent<Engine::RenderComponent>(vertices, indexes,
                                                       m_Shader, 50, 50);

        vertices = {
            -1.0, -1.0, 0.0, 0.0, 0.0, 1.0,

            -1.0, 1.0,  0.0, 0.0, 0.0, 1.0,

            1.0,  -1.0, 0.0, 0.0, 0.0, 1.0,

            1.0,  1.0,  0.0, 0.0, 0.0, 1.0,
        };

        indexes = {0, 1, 2, 1, 3, 2};

        m_Lift = addEntity("lift");
        m_Lift->addComponent<Engine::LocationComponent>(350.0, 75.0, 0);
        m_Lift->addComponent<Engine::VelocityComponent>(0, 0);
        m_Lift->addComponent<Engine::ObstacleComponent>();
        m_Lift->addComponent<Engine::CollisionComponent>(50, 50);
        m_Lift->addComponent<Engine::RenderComponent>(vertices, indexes,
                                                      m_Shader, 50, 50);

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", m_Lift.get());

        auto moveUpBlackboard = std::make_shared<Engine::Blackboard>();
        moveUpBlackboard->setFloat("targetX", 350.0f);
        moveUpBlackboard->setFloat("targetY", 300.0f);

        auto moveDownBlackboard = std::make_shared<Engine::Blackboard>();
        moveDownBlackboard->setFloat("targetX", 350.0f);
        moveDownBlackboard->setFloat("targetY", 75.0f);

        auto behaviourTree = new Engine::BlackboardManager(
            blackboard,
            new Engine::UntilFail(new Engine::SequenceTask(
                {new Engine::BlackboardManager(moveUpBlackboard,
                                               new Engine::MoveTask()),

                 new Engine::BlackboardManager(moveDownBlackboard,
                                               new Engine::MoveTask())})));

        m_Lift->addComponent<Engine::AIComponent>(behaviourTree);

        vertices = {
            -1.0, -1.0, 0.0, 0.0, 0.0, 1.0,

            -1.0, 1.0,  0.0, 0.0, 0.0, 1.0,

            1.0,  -1.0, 0.0, 0.0, 0.0, 1.0,

            1.0,  1.0,  0.0, 0.0, 0.0, 1.0,
        };

        indexes = {0, 1, 2, 1, 3, 2};

        auto entity2 = addEntity("box");
        entity2->addComponent<Engine::LocationComponent>(300.0, 25.0, 0);
        entity2->addComponent<Engine::ObstacleComponent>();
        entity2->addComponent<Engine::CollisionComponent>(600, 50);
        entity2->addComponent<Engine::RenderComponent>(vertices, indexes,
                                                       m_Shader, 600, 50);

        vertices = {
            -1.0, -1.0, 0.0, 0.0, 0.0, 1.0,

            -1.0, 1.0,  0.0, 0.0, 0.0, 1.0,

            1.0,  -1.0, 0.0, 0.0, 0.0, 1.0,
        };

        indexes = {0, 1, 2};

        auto entity6 = addEntity("box");
        entity6->addComponent<Engine::LocationComponent>(100.0, 75.0, 0);
        entity6->addComponent<Engine::ObstacleComponent>();
        entity6->addComponent<Engine::SlopeComponent>(true);
        entity6->addComponent<Engine::CollisionComponent>(50, 50);
        entity6->addComponent<Engine::RenderComponent>(vertices, indexes,
                                                       m_Shader, 50, 50);

        vertices = {
            -1.0, -1.0, 0.0, 0.0, 0.0, 1.0,

            1.0,  1.0,  0.0, 0.0, 0.0, 1.0,

            1.0,  -1.0, 0.0, 0.0, 0.0, 1.0,
        };

        indexes = {0, 1, 2};

        auto entity7 = addEntity("box");
        entity7->addComponent<Engine::LocationComponent>(200.0, 75.0, 0);
        entity7->addComponent<Engine::ObstacleComponent>();
        entity7->addComponent<Engine::SlopeComponent>(false);
        entity7->addComponent<Engine::CollisionComponent>(50, 50);
        entity7->addComponent<Engine::RenderComponent>(vertices, indexes,
                                                       m_Shader, 50, 50);

        vertices = {
            -1.0, -1.0, 0.0, 0.0, 1.0, 0.0,

            -1.0, 1.0,  0.0, 0.0, 1.0, 0.0,

            1.0,  -1.0, 0.0, 0.0, 1.0, 0.0,

            1.0,  1.0,  0.0, 0.0, 1.0, 0.0,
        };

        indexes = {0, 1, 2, 1, 3, 2};

        m_Player = addEntity("player");
        m_Player->addComponent<Engine::CameraComponent>();
        m_Player->addComponent<Engine::LocationComponent>(250.0, 150.0, 0);
        m_Player->addComponent<Engine::VelocityComponent>(2, 0);
        m_Player->addComponent<Engine::CollisionComponent>(25, 25);
        m_Player->addComponent<Engine::RigitBodyComponent>(1);
        m_Player->addComponent<Engine::RenderComponent>(vertices, indexes,
                                                        m_Shader, 25, 25);
    }

    virtual void onUpdate() override {
        auto &input = Engine::Application::get().getInput();
        auto velocity = m_Player->getComponent<Engine::VelocityComponent>();

        if (input.IsKeyPressed(Engine::KeyCode::A)) {
            velocity->x = -3;
        } else if (input.IsKeyPressed(Engine::KeyCode::D)) {
            velocity->x = 3;
        } else {
            velocity->x = 0;
        }

        if (input.IsKeyPressed(Engine::KeyCode::Space)) {
            velocity->y = 4;
        }
    }

    virtual void onMouseEvent(Engine::MouseEvent &e) override {
        if (e.type == Engine::EventType::MouseDown) {
            auto location = m_Player->getComponent<Engine::LocationComponent>();
            auto velocity = m_Player->getComponent<Engine::VelocityComponent>();
            location->x = 100;
            location->y = 100;
            velocity->y = 0;
        }
    }
};

class MyApp : public Engine::Application {
  public:
    MyApp() { addLayer(new MyLayer()); }

    virtual ~MyApp() {}
};

Engine::Application *Engine::createApplication() { return new MyApp(); }
