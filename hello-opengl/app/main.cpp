#include "AIComponent.hpp"
#include "AnimationComponent.hpp"
#include "Application.hpp"
#include "BlackboardManager.hpp"
#include "CameraComponent.hpp"
#include "CollisionComponent.hpp"
#include "ControllerTask.hpp"
#include "EntryPoint.hpp"
#include "FlyTask.hpp"
#include "GroundComponent.hpp"
#include "Inverter.hpp"
#include "JumpTask.hpp"
#include "KeyboardControlComponent.hpp"
#include "LocationComponent.hpp"
#include "MorphingComponent.hpp"
#include "MoveLeftTask.hpp"
#include "MoveRightTask.hpp"
#include "ObstacleComponent.hpp"
#include "OnGroundTask.hpp"
#include "ParallelTask.hpp"
#include "RenderComponent.hpp"
#include "RigitBodyComponent.hpp"
#include "SelectorTask.hpp"
#include "SequenceTask.hpp"
#include "TextureComponent.hpp"
#include "UntilFail.hpp"
#include "VelocityComponent.hpp"
#include "WaitTask.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>

const std::string textureVertexShader = R"(#version 330 core
                                    layout (location = 0) in vec3 a_position;
                                    layout (location = 1) in vec2 a_texCoord;

                                    uniform mat2x3 model;
                                    uniform mat2x3 texture_model;

                                    out vec2 v_texCoord;
                                    
                                    void main()
                                    {
                                      vec2 pos = vec3(a_position.xy, 1.0f) * model;
                                      gl_Position = vec4(pos, a_position.z, 1.0f);
                                      v_texCoord = vec3(a_texCoord, 1.0f) * texture_model;
                                    }
                                    )";

const std::string textureFragmentShader = R"(#version 330 core
                                    in vec2 v_texCoord;

                                    uniform sampler2D s_texture;

                                    out vec4 v_color;
                                    
                                    void main()
                                    {
                                      vec4 texture_color = texture(s_texture, v_texCoord);
                                      vec3 darkened = mix(vec3(texture_color.rgb), vec3(0,0,0), 0.1);

                                      v_color = texture(s_texture, v_texCoord);
                                    }
                                    )";

const std::string morphingVertexShader = R"(#version 330 core
                                    layout (location = 0) in vec3 from_position;
                                    layout (location = 1) in vec3 from_color;
                                    layout (location = 2) in vec3 to_position;
                                    layout (location = 3) in vec3 to_color;

                                    uniform mat4 MVP;
                                    uniform float time;

                                    out vec3 v_color;
                                    
                                    void main()
                                    {
                                      float t = (sin(time) + 1) / 2;
                                      v_color = from_color + (to_color - from_color) * t;
                                      vec3 a_position = from_position + (to_position - from_position) * t;

                                      gl_Position = MVP * vec4(a_position, 1.0f);
                                    }
                                    )";

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

                                    out vec4 vColor;
                                    
                                    void main()
                                    {
                                      vColor = vec4(v_color, 1.0f);
                                    }
                                    )";

class MyLayer : public Engine::Layer {
  private:
    std::shared_ptr<Engine::Shader> m_Shader;
    std::shared_ptr<Engine::Shader> m_MorphingShader;
    std::shared_ptr<Engine::Shader> m_TextureShader;
    std::shared_ptr<Engine::Entity> m_Player;
    std::shared_ptr<Engine::Entity> m_Lift;

  public:
    virtual void onAttach() override {
        auto &app = Engine::Application::get();
        auto &textures = app.getTextures();

        textures.load("stairs", "./assets/stairs.png");
        textures.load("mill", "./assets/mill.png");
        textures.load("stairs", "./assets/stairs.png");
        textures.load("grass-low", "./assets/grass-low.png");
        textures.load("firewood", "./assets/firewood.png");
        textures.load("lumberjack", "./assets/lumberjack.png");
        textures.load("stumb-2", "./assets/stumb-2.png");
        textures.load("falled-tree", "./assets/falled-tree.png");
        textures.load("home", "./assets/home.png");
        textures.load("grandmother", "./assets/grandmother.png");
        textures.load("tree-1", "./assets/tree-1.png");
        textures.load("characters", "./assets/characters.png");
        textures.load("background", "./assets/background.png");
        textures.load("front", "./assets/front.png");
        textures.load("slope", "./assets/slope.png");
        textures.load("slope-front", "./assets/slope-front.png");
        textures.load("chickens", "./assets/chickens.png");

        m_Shader.reset(Engine::Shader::create(vertexShader, fragmentShader));

        ////////////////////////////////////////////////////////////////
        // Sky /////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////

        std::vector<float> vertices = {
            -1.0, -1.0, 0.0, 0.0, 0.06, 0.06,

            -1.0, 1.0,  0.0, 0.0, 0.06, 0.06,

            1.0,  -1.0, 0.0, 0.0, 0.06, 0.06,

            1.0,  1.0,  0.0, 0.0, 0.06, 0.06,
        };

        std::vector<uint32_t> indexes = {0, 1, 2, 1, 3, 2};

        auto sky = addEntity("sky");
        sky->addComponent<Engine::LocationComponent>(480.0, 470.0, true);
        sky->addComponent<Engine::RenderComponent>(vertices, indexes, m_Shader,
                                                   960, 150);

        vertices = {
            -1.0, -1.0, 0.0, 0.0, 0.17, 0.15,

            -1.0, 1.0,  0.0, 0.0, 0.17, 0.15,

            1.0,  -1.0, 0.0, 0.0, 0.17, 0.15,

            1.0,  1.0,  0.0, 0.0, 0.17, 0.15,
        };

        auto frontFill = addEntity("frontFill");
        frontFill->addComponent<Engine::LocationComponent>(400.0, 60.0);
        frontFill->addComponent<Engine::RenderComponent>(vertices, indexes,
                                                         m_Shader, 800, 120);

        auto ground = addEntity("ground-1");
        ground->addComponent<Engine::LocationComponent>(400.0, 175.0);
        ground->addComponent<Engine::ObstacleComponent>();
        ground->addComponent<Engine::CollisionComponent>(800, 50);
        ground->addComponent<Engine::GroundComponent>();

        // 800 1030 915
        // 200 90
        auto slope = addEntity("slope");
        std::vector<Engine::Vec2> collider = {
            Engine::Vec2(0, 0), Engine::Vec2(0, -119), Engine::Vec2(235, -119)};

        slope->addComponent<Engine::LocationComponent>(800, 200.0);
        slope->addComponent<Engine::ObstacleComponent>();
        slope->addComponent<Engine::CollisionComponent>(collider);
        slope->addComponent<Engine::GroundComponent>();

        ground = addEntity("ground-2");
        ground->addComponent<Engine::LocationComponent>(1430.0, 65.0);
        ground->addComponent<Engine::ObstacleComponent>();
        ground->addComponent<Engine::CollisionComponent>(800, 50);
        ground->addComponent<Engine::GroundComponent>();

        ////////////////////////////////////////////////////////////////
        // Textures ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        m_TextureShader.reset(
            Engine::Shader::create(textureVertexShader, textureFragmentShader));

        //////////////////////////////////////////////////////////////
        // Texture - Forest //////////////////////////////////////////
        //////////////////////////////////////////////////////////////

        auto background = addEntity("background");
        background->addComponent<Engine::LocationComponent>(400, 370.0);
        background->addComponent<Engine::TextureComponent>(
            "background", Engine::Rect(0, 0, 1, 1), 800, 275, m_TextureShader);

        auto front = addEntity("front");
        front->addComponent<Engine::LocationComponent>(400, 145.0);
        front->addComponent<Engine::TextureComponent>(
            "front", Engine::Rect(0, 0, 1, 1), 800, 75, m_TextureShader);

        background = addEntity("background");
        background->addComponent<Engine::LocationComponent>(1430, 260.0);
        background->addComponent<Engine::TextureComponent>(
            "background", Engine::Rect(0, 0, 1, 1), 800, 275, m_TextureShader);

        front = addEntity("front");
        front->addComponent<Engine::LocationComponent>(1430, 35.0);
        front->addComponent<Engine::TextureComponent>(
            "front", Engine::Rect(0, 0, 1, 1), 800, 75, m_TextureShader);

        auto slopeBackground = addEntity("slopeBackground");
        slopeBackground->addComponent<Engine::LocationComponent>(900, 300.0);
        slopeBackground->addComponent<Engine::TextureComponent>(
            "slope", Engine::Rect(0, 0, 1, 1), 310, 350, m_TextureShader);

        auto slopeFront = addEntity("slopeFront");
        slopeFront->addComponent<Engine::LocationComponent>(910, 80.0);
        slopeFront->addComponent<Engine::TextureComponent>(
            "slope-front", Engine::Rect(0, 0, 1, 1), 265, 160, m_TextureShader);

        ////////////////////////////////////////////////////////////////
        // Texture - Mill //////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        // auto mill = addEntity("mill");
        // mill->addComponent<Engine::LocationComponent>(200.0, 235.0, 0);
        // mill->addComponent<Engine::TextureComponent>("mill",
        //                                              textVertices,
        //                                              textIndexes,
        //                                              m_TextureShader, 330,
        //                                              350);

        ////////////////////////////////////////////////////////////////
        // Texture - Stairs ////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        // for (size_t i = 0; i < 5; i++) {
        //     auto stairs = addEntity("stairs");
        //     stairs->addComponent<Engine::LocationComponent>(350.0 + i * 16,
        //                                                     205.0 + i * 16);
        //     stairs->addComponent<Engine::TextureComponent>(
        //         "stairs", textVertices, textIndexes, m_TextureShader, 50,
        //         20);
        // }

        // auto stairsSlope = addEntity("stairs-slope");
        // collider = {Engine::Vec2(0, -5), Engine::Vec2(80, 75),
        //             Engine::Vec2(80, -5)};

        // stairsSlope->addComponent<Engine::LocationComponent>(340.0, 200.0);
        // stairsSlope->addComponent<Engine::ObstacleComponent>();
        // stairsSlope->addComponent<Engine::CollisionComponent>(collider);

        ////////////////////////////////////////////////////////////////
        // Texture - Grass //////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        auto grass = addEntity("grass");
        grass->addComponent<Engine::LocationComponent>(500.0, 205.0);
        grass->addComponent<Engine::TextureComponent>(
            "grass-low", Engine::Rect(0, 0, 1, 1), 186, 56, m_TextureShader);

        auto grass2 = addEntity("grass");
        grass2->addComponent<Engine::LocationComponent>(1140.0, 92.0);
        grass2->addComponent<Engine::TextureComponent>(
            "grass-low", Engine::Rect(0, 0, 1, 1), 186, 56, m_TextureShader);

        auto grass3 = addEntity("grass");
        grass3->addComponent<Engine::LocationComponent>(1400.0, 100.0);
        grass3->addComponent<Engine::TextureComponent>(
            "grass-low", Engine::Rect(0, 0, 1, 1), 186, 56, m_TextureShader);

        ////////////////////////////////////////////////////////////////
        // Texture - Lumberjack ////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        auto fireWood = addEntity("fireWood");
        fireWood->addComponent<Engine::LocationComponent>(620.0, 215.0);
        fireWood->addComponent<Engine::TextureComponent>(
            "firewood", Engine::Rect(0, 0, 1, 1), 35, 15, m_TextureShader);

        auto fireWood2 = addEntity("fireWood");
        fireWood2->addComponent<Engine::LocationComponent>(640.0, 215.0);
        fireWood2->addComponent<Engine::TextureComponent>(
            "firewood", Engine::Rect(0, 0, 1, 1), 35, 15, m_TextureShader);

        auto lumberjack = addEntity("lumberjack");
        lumberjack->addComponent<Engine::LocationComponent>(650.0, 230.0);
        lumberjack->addComponent<Engine::TextureComponent>(
            "lumberjack", Engine::Rect(0, 0, 1, 1), 38, 58, m_TextureShader);

        auto lumberjackStumb = addEntity("lumberjack-stumb");
        lumberjackStumb->addComponent<Engine::LocationComponent>(700.0, 210.0);
        lumberjackStumb->addComponent<Engine::TextureComponent>(
            "stumb-2", Engine::Rect(0, 0, 1, 1), 38, 32, m_TextureShader);
        lumberjackStumb->addComponent<Engine::ObstacleComponent>();
        lumberjackStumb->addComponent<Engine::CollisionComponent>(25, 32);
        lumberjackStumb->addComponent<Engine::GroundComponent>();

        // auto falledTree = addEntity("lumberjack-falled-tree");
        // falledTree->addComponent<Engine::LocationComponent>(940.0, 217.0);
        // falledTree->addComponent<Engine::TextureComponent>(
        //     "falled-tree", textVertices, textIndexes, m_TextureShader, 166,
        //     39);
        // falledTree->addComponent<Engine::ObstacleComponent>();
        // falledTree->addComponent<Engine::CollisionComponent>(145, 16);

        ////////////////////////////////////////////////////////////////
        // Texture - Home //////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        auto home = addEntity("home");
        home->addComponent<Engine::LocationComponent>(1400.0, 160.0);
        home->addComponent<Engine::TextureComponent>(
            "home", Engine::Rect(0, 0, 1, 1), 240, 135, m_TextureShader);

        ////////////////////////////////////////////////////////////////
        // Texture - Grandmother ///////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        auto grandmother = addEntity("grandmother");
        grandmother->addComponent<Engine::LocationComponent>(1300.0, 110.0);
        grandmother->addComponent<Engine::TextureComponent>(
            "grandmother", Engine::Rect(0, 0, 1, 1), 30, 45, m_TextureShader);

        ////////////////////////////////////////////////////////////////
        // Texture - Chicken ///////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        {
            auto chicken = addEntity("chicken");
            auto move = Engine::Animation(0, 32.0 / 196.0, 3, 0.35);
            auto wait = Engine::Animation(25.0 / 100.0, 32.0 / 196.0, 5, 0.7);

            chicken->addComponent<Engine::LocationComponent>(1100.0, 110.0);
            chicken->addComponent<Engine::AnimationComponent>(wait, move);
            chicken->addComponent<Engine::TextureComponent>(
                "chickens", Engine::Rect(0, 0, 32.0 / 196.0, 25.0 / 100.0), 32,
                25, m_TextureShader);
            chicken->addComponent<Engine::VelocityComponent>(0, 0);
        }

        {
            auto chicken = addEntity("chicken");
            auto move = Engine::Animation(0, 32.0 / 196.0, 3, 0.35);
            auto wait = Engine::Animation(25.0 / 100.0, 32.0 / 196.0, 5, 0.7);

            chicken->addComponent<Engine::LocationComponent>(1170.0, 115.0);
            chicken->addComponent<Engine::AnimationComponent>(wait, move);
            chicken->addComponent<Engine::TextureComponent>(
                "chickens", Engine::Rect(0, 0, 32.0 / 196.0, 25.0 / 100.0), 32,
                25, m_TextureShader);
            chicken->addComponent<Engine::VelocityComponent>(0, 0);
        }

        {
            auto chicken = addEntity("chicken");
            auto move = Engine::Animation(0, 32.0 / 196.0, 3, 0.35);
            auto wait = Engine::Animation(25.0 / 100.0, 32.0 / 196.0, 6, 0.7);

            chicken->addComponent<Engine::LocationComponent>(1150.0, 120.0);
            chicken->addComponent<Engine::AnimationComponent>(wait, move);
            chicken->addComponent<Engine::TextureComponent>(
                "chickens",
                Engine::Rect(0, 25.0 * 2.0 / 100.0, 32.0 / 196.0, 25.0 / 100.0),
                32, 25, m_TextureShader);
            chicken->addComponent<Engine::VelocityComponent>(0, 0);
        }

        ////////////////////////////////////////////////////////////////
        // Texture - Tree //////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        auto tree = addEntity("tree");
        tree->addComponent<Engine::LocationComponent>(150.0, 280.0);
        tree->addComponent<Engine::TextureComponent>(
            "tree-1", Engine::Rect(0, 0, 1, 1), 170, 172, m_TextureShader);
        tree->addComponent<Engine::ObstacleComponent>();
        tree->addComponent<Engine::CollisionComponent>(20, 200);

        ////////////////////////////////////////////////////////////////
        // Player //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        m_Player = addEntity("player");

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", m_Player.get());
        blackboard->setFloat("speedX", 2.0);
        blackboard->setFloat("speedY", 7.0);

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::ParallelTask({
                    new Engine::SequenceTask({
                        new Engine::OnGroundTask(),
                        new Engine::ControllerTask(Engine::KeyCode::Space),
                        new Engine::JumpTask(),
                    }),

                    new Engine::SequenceTask({
                        new Engine::ControllerTask(Engine::KeyCode::A),
                        new Engine::MoveLeftTask(),
                    }),

                    new Engine::SequenceTask({
                        new Engine::ControllerTask(Engine::KeyCode::D),
                        new Engine::MoveRightTask(),
                    }),
                }),

                new Engine::WaitTask()
            })
        );
        // clang-format on

        float w = 54.0 / 340.0;
        float h = 54.0 / 270.0;

        auto wait = Engine::Animation(0, w, 1, 0.35);
        auto move = Engine::Animation(0, w, 3, 0.35);

        m_Player->addComponent<Engine::AIComponent>(state);
        m_Player->addComponent<Engine::CameraComponent>(0, 5000, -200);
        m_Player->addComponent<Engine::LocationComponent>(250.0, 250.0);
        m_Player->addComponent<Engine::VelocityComponent>(0, 0);
        m_Player->addComponent<Engine::CollisionComponent>(14, 50);
        m_Player->addComponent<Engine::RigitBodyComponent>(0.5);
        m_Player->addComponent<Engine::AnimationComponent>(wait, move);
        m_Player->addComponent<Engine::TextureComponent>(
            "characters", Engine::Rect(0, 0, w, h), 54, 54, m_TextureShader);

        app.getEventHandler().add<Engine::BeginCollisionEvent>(
            std::bind(&MyLayer::beginCollision, this, std::placeholders::_1));
    }

    void beginCollision(Engine::BeginCollisionEvent &event) {
        // std::cout << event.first << " " << event.second << std::endl;
    }

    void beginInte(Engine::BeginCollisionEvent &event) {
        // std::cout << event.first << " " << event.second << std::endl;
    }

    virtual void onUpdate() override {}

    virtual void onMouseEvent(Engine::MouseEvent &e) override {
        if (e.type == Engine::EventType::MouseDown) {
            auto location = m_Player->getComponent<Engine::LocationComponent>();
            auto velocity = m_Player->getComponent<Engine::VelocityComponent>();
            location->x = 250;
            location->y = 300;
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
