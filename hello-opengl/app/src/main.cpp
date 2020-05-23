#include "AIComponent.hpp"
#include "Application.hpp"
#include "BlackboardManager.hpp"
#include "ControllerTask.hpp"
#include "EntryPoint.hpp"
#include "FlyTask.hpp"
#include "ImGuiLayer.hpp"
#include "Inverter.hpp"
#include "JumpTask.hpp"
#include "MoveLeftTask.hpp"
#include "MoveRightTask.hpp"
#include "OnGroundTask.hpp"
#include "ParallelTask.hpp"
#include "SelectorTask.hpp"
#include "SequenceTask.hpp"
#include "TimeLine.hpp"
#include "UntilFail.hpp"
#include "WaitTask.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>

class MyLayer : public Engine::Layer {
  private:
    std::shared_ptr<Engine::Entity> m_Player;

  public:
    virtual void onAttach() override {
        load("./levels/level1.txt");

        auto &app = Engine::Application::get();

        m_Player = getEntity("player");

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

        m_Player->addComponent<Engine::AIComponent>(state);

        ////////////////////////////////////////////////////////////////
        // Events //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////
        app.getEventHandler().add<Engine::BeginCollisionEvent>(
            std::bind(&MyLayer::beginCollision, this, std::placeholders::_1));
    }

    void beginCollision(Engine::BeginCollisionEvent &event) {
        // std::cout << event.first << " " << event.second << std::endl;
    }

    virtual void onUpdate() override {}

    virtual void onMouseEvent(Engine::MouseEvent &e) override {
        // if (e.type == Engine::EventType::MouseDown) {
        //     auto location =
        //     m_Player->getComponent<Engine::LocationComponent>(); auto
        //     velocity = m_Player->getComponent<Engine::VelocityComponent>();
        //     location->x = 1550;
        //     location->y = 300;
        //     velocity->y = 0;
        // }
    }
};

class MyApp : public Engine::Application {
  public:
    MyApp() {
        addLayer(new MyLayer());
        addLayer(new Engine::ImGuiLayer());
    }

    virtual ~MyApp() {}
};

Engine::Application *Engine::createApplication() { return new MyApp(); }
