#include "GameScreen.hpp"
#include "ScreenManager.hpp"

#include "BehaviourTree.hpp"
#include "ECS.hpp"

GameScreen::GameScreen() {}

void GameScreen::load(Context *context) {
    context->load("./config/game.txt");

    auto &app = Engine::Application::get();

    m_Player = context->getEntity("player");

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

    app.getSound().play("background", 0.5);
}

void GameScreen::update() {
    auto &input = Engine::Application::get().getInput();

    Engine::Vec2 pos = input.GetMousePosition();

    if (input.IsKeyPressed(Engine::KeyCode::Escape)) {
        ScreenManager::get().goTo("pause");
    }

    if (input.IsKeyPressed(Engine::KeyCode::F)) {
        if (m_FPressed) {
            return;
        }
        m_FPressed = true;
        bool isAactive =
            m_Player->getComponent<Engine::SpotLightComponent>()->isActive;
        m_Player->getComponent<Engine::SpotLightComponent>()->isActive =
            !isAactive;
    } else {
        m_FPressed = false;
    }
}

void GameScreen::unload(Context *context) { context->clear(); }