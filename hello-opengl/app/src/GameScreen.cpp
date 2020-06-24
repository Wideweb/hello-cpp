#include "GameScreen.hpp"
#include "ScreenManager.hpp"

#include "BehaviourTree.hpp"
#include "ECS.hpp"

GameScreen::GameScreen() {}

void GameScreen::load(Context *context) {
    context->load("./config/game.txt");

    auto &app = Engine::Application::get();

    {
        m_Player = context->getEntity("player");

        m_FlashLight = context->getEntity("player-flashlight");
        m_Player->getComponent<Engine::AttackComponent>()->isActive = false;

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", m_Player.get());
        blackboard->setFloat("speedX", 2.0);
        blackboard->setFloat("speedY", 7.0);

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::DieTask(),

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
    }

    {
        auto wolf = context->getEntity("wolf");

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", wolf.get());
        blackboard->setPtr("target", m_Player.get());
        blackboard->setFloat("runSpeed", 4.0);
        blackboard->setFloat("runDistance", 1700);

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::SequenceTask({
                    new Engine::DieTask(),
                    new Engine::StopSteeringTask(),
                    new Engine::RunAwayTask(),
                }),
                new Engine::SteeringTask(),
            })
        );
        // clang-format on
        wolf->addComponent<Engine::AIComponent>(state);
    }

    app.getSound().play("background", 0.5,
                        Engine::SoundBuffer::Properties::Looped);
    {
        auto wolf = context->getEntity("wolf1");

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", wolf.get());
        blackboard->setPtr("target", m_Player.get());
        blackboard->setFloat("runSpeed", 3.0);
        blackboard->setFloat("runDistance", 700);

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::SequenceTask({
                    new Engine::DieTask(),
                    new Engine::StopSteeringTask(),
                    new Engine::RunAwayTask(),
                }),
                new Engine::SteeringTask(),
            })
        );
        // clang-format on
        wolf->addComponent<Engine::AIComponent>(state);
    }

    {
        auto wolf = context->getEntity("wolf2");

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", wolf.get());
        blackboard->setPtr("target", m_Player.get());
        blackboard->setFloat("runSpeed", 3.0);
        blackboard->setFloat("runDistance", 700);

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::SequenceTask({
                    new Engine::DieTask(),
                    new Engine::StopSteeringTask(),
                    new Engine::RunAwayTask(),
                }),
                new Engine::SteeringTask(),
            })
        );
        // clang-format on
        wolf->addComponent<Engine::AIComponent>(state);
    }

    {
        auto wolf = context->getEntity("wolf3");

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", wolf.get());
        blackboard->setPtr("target", m_Player.get());
        blackboard->setFloat("runSpeed", 3.0);
        blackboard->setFloat("runDistance", 700);

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::SequenceTask({
                    new Engine::DieTask(),
                    new Engine::StopSteeringTask(),
                    new Engine::RunAwayTask(),
                }),
                new Engine::SteeringTask(),
            })
        );
        // clang-format on
        wolf->addComponent<Engine::AIComponent>(state);
    }

    {
        auto mom = context->getEntity("mom");

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", mom.get());
        blackboard->setPtr("target", m_Player.get());
        blackboard->setFloat("distance", 200.0);

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::SequenceTask({
                    new Engine::DistanceLessThanTask(),
                    new Engine::LookAtTask(),
                    new Engine::BeginInteractionTask(),
                }),
                new Engine::SequenceTask({
                    new Engine::IsInteractionTask(),
                    new Engine::Inverter(new Engine::DistanceLessThanTask()),
                    new Engine::EndInteractionTask(),
                    new Engine::VisitTask(),
                })
            })
        );
        // clang-format on
        mom->addComponent<Engine::AIComponent>(state);
    }

    {
        auto mom = context->getEntity("mom");
        auto text = context->getEntity("mom-text");
        text->getComponent<Engine::TextureComponent>()->isActive = false;

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", text.get());
        blackboard->setPtr("target", m_Player.get());
        blackboard->setFloat("distance", 200.0);
        blackboard->setInt("frame", 1);

        auto momBlackboard = std::make_shared<Engine::Blackboard>();
        momBlackboard->setPtr("entity", mom.get());

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::SequenceTask({
                    new Engine::BlackboardManager(
                        momBlackboard,
                        new Engine::Inverter(new Engine::IsInteractionTask())
                    ),
                    new Engine::HideTask()
                }),


                new Engine::SequenceTask({
                    new Engine::BlackboardManager(
                        momBlackboard,
                        new Engine::isVisitedTask()
                    ),
                    new Engine::SetFrameTask(),
                    new Engine::ShowTask(),   
                }),
                
                new Engine::ShowTask(),
            })
        );
        // clang-format on
        text->addComponent<Engine::AIComponent>(state);
    }

    {
        auto boy = context->getEntity("little-boy");
        auto mom = context->getEntity("mom");

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", boy.get());
        blackboard->setPtr("target", m_Player.get());
        blackboard->setFloat("distance", 210.0);
        blackboard->setFloat("speedX", 1);

        auto leadBlackboard = std::make_shared<Engine::Blackboard>();
        leadBlackboard->setFloat("distance", 150.0);

        auto steeringBlackboard = std::make_shared<Engine::Blackboard>();
        steeringBlackboard->setPtr("target", mom.get());
        steeringBlackboard->setFloat("distance", 50.0);

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::SequenceTask({
                    new Engine::BlackboardManager({
                        leadBlackboard,
                        new Engine::DistanceLessThanTask(),
                    }),
                    new Engine::EndInteractionTask(),
                    new Engine::VisitTask(),
                    new Engine::BlackboardManager({
                        steeringBlackboard,
                        new Engine::SelectorTask({
                            new Engine::SequenceTask({
                                new Engine::Inverter(new Engine::DistanceLessThanTask()),
                                new Engine::MoveLeftTask()
                            }),
                        }),
                    }),
                }),

                new Engine::SequenceTask({
                    new Engine::DistanceLessThanTask(),
                    new Engine::WaitTask(),
                    new Engine::LookAtTask(),
                    new Engine::BeginInteractionTask(),
                }),

                new Engine::SequenceTask({
                    new Engine::IsInteractionTask(),
                    new Engine::Inverter(new Engine::DistanceLessThanTask()),
                    new Engine::EndInteractionTask(),
                    new Engine::VisitTask(),
                }),

                new Engine::SequenceTask({
                    new Engine::Inverter(new Engine::isVisitedTask()),
                    new Engine::MoveRightTask(),
                }),

                new Engine::WaitTask()
            })
        );
        // clang-format on
        boy->addComponent<Engine::AIComponent>(state);
    }

    {
        auto text = context->getEntity("little-boy-text");
        auto boy = context->getEntity("little-boy");
        auto mom = context->getEntity("mom");
        text->getComponent<Engine::TextureComponent>()->isActive = false;

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("parent", boy.get());
        blackboard->setPtr("entity", text.get());
        blackboard->setPtr("target", m_Player.get());
        blackboard->setFloat("distance", 150.0);
        blackboard->setInt("frame", 1);

        auto boyBlackboard = std::make_shared<Engine::Blackboard>();
        boyBlackboard->setPtr("entity", boy.get());

        auto momBlackboard = std::make_shared<Engine::Blackboard>();
        momBlackboard->setPtr("entity", mom.get());

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::SequenceTask({
                    new Engine::BlackboardManager(
                        momBlackboard,
                        new Engine::SelectorTask({
                            new Engine::IsInteractionTask(),
                            new Engine::isVisitedTask(),
                        })
                    ),
                    new Engine::HideTask()
                }),

                new Engine::SequenceTask({
                    new Engine::BlackboardManager(
                        boyBlackboard,
                        new Engine::Inverter(new Engine::IsInteractionTask())
                    ),
                    new Engine::HideTask()
                }),

                new Engine::SequenceTask({
                    new Engine::BlackboardManager(
                        boyBlackboard,
                        new Engine::isVisitedTask()
                    ),
                    new Engine::SetFrameTask(),
                    new Engine::ShowTask(),   
                }),
                
                new Engine::ShowTask(),
            })
        );
        // clang-format on
        text->addComponent<Engine::AIComponent>(state);
    }

    {
        auto text = context->getEntity("grand-father-text");

        auto blackboard = std::make_shared<Engine::Blackboard>();
        blackboard->setPtr("entity", text.get());
        blackboard->setPtr("target", m_Player.get());
        blackboard->setFloat("distance", 200.0);

        // clang-format off
        auto state = new Engine::BlackboardManager(
            blackboard,
            new Engine::SelectorTask({
                new Engine::SequenceTask({
                    new Engine::DistanceLessThanTask(),
                    new Engine::ShowTask(),
                }),
                new Engine::HideTask(),
            })
        );
        // clang-format on
        text->addComponent<Engine::AIComponent>(state);
    }

    m_Actions.add(new StopSoundAction(1050, 0, "background"));
    m_Actions.add(new PlaySoundAction(1050, 0, "horror", 1.0,
                                      Engine::SoundBuffer::Properties::Looped));
    m_Actions.add(new FirstWolfAction(1500, 0));
    m_Actions.add(new PlaySoundAction(1500, 0, "incoming", 1.0,
                                      Engine::SoundBuffer::Properties::Looped));
    m_Actions.add(new TakeLighterAction(2100, 0));
    m_Actions.add(new WolfIsGone())
        ->then(new StopSoundAction(0, 0, "horror"))
        ->then(new StopSoundAction(0, 0, "incoming"))
        ->then(new PlaySoundAction(0, 0, "background", 1.0,
                                   Engine::SoundBuffer::Properties::Looped));
    m_Actions.add(new RainAction(2500, 0));
    m_Actions.add(new PlaySoundAction(2500, 1.0, "rain", 0.3,
                                      Engine::SoundBuffer::Properties::Looped));
    m_Actions.add(new TurnOffFlashLightAction(3000, 0));

    m_Actions.add(new StopSoundAction(3200, 0, "background"));
    m_Actions.add(new PlaySoundAction(3200, 0, "horror", 1.0,
                                      Engine::SoundBuffer::Properties::Looped));
    m_Actions.add(new PlaySoundAction(3200, 0, "incoming", 1.0,
                                      Engine::SoundBuffer::Properties::Looped));

    m_Actions.add(new WolfsAction(3200, 0));

    m_Actions.add(new ThunderAction(3600, 0))
        ->then(new StopSoundAction(0, 0, "horror"))
        ->then(new StopSoundAction(0, 0, "incoming"))
        ->then(new PlaySoundAction(0, 0, "background", 1.0,
                                   Engine::SoundBuffer::Properties::Looped))
        ->then(new GrandSun());

    m_Actions.add(new StopRainAction(3600, 0));
    m_Actions.add(new StopSoundAction(3600, 3.0, "rain"));
    m_Actions.init(context);
}

void GameScreen::update() {
    m_Water.update();

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
            m_FlashLight->getComponent<Engine::SpotLightComponent>()->isActive;
        m_FlashLight->getComponent<Engine::SpotLightComponent>()->isActive =
            !isAactive;
        m_Player->getComponent<Engine::AttackComponent>()->isActive =
            !isAactive;
    } else {
        m_FPressed = false;
    }

    if (m_Player->hasComponent<Engine::DieComponent>()) {
        ScreenManager::get().goTo("menu");
    }

    m_Actions.update();
}

void GameScreen::unload(Context *context) { context->clear(); }
