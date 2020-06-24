#include "GameScreen.hpp"
#include "MenuScreen.hpp"
#include "PauseScreen.hpp"
#include "ScreenManager.hpp"
#include "TitleScreen.hpp"

#include "Application.hpp"
#include "EntryPoint.hpp"
#include "ImGuiLayer.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>

class AppLayer : public Engine::Layer {
  private:
    std::shared_ptr<ScreenManager> m_ScreenManager;

  public:
    virtual void onAttach() override {
        auto startMenu =
            new Menu({MenuItem("new-game", MenuItemLinkType::Screen, "game"),
                      MenuItem("exit", MenuItemLinkType::Exit)});

        auto pauseMenu =
            new Menu({MenuItem("resume", MenuItemLinkType::Screen, "game"),
                      MenuItem("new-game", MenuItemLinkType::Screen, "game"),
                      MenuItem("exit", MenuItemLinkType::Exit)});

        m_ScreenManager.reset(new ScreenManager());
        m_ScreenManager->init(this);
        m_ScreenManager->add("title", new TitleScreen());
        m_ScreenManager->add("menu", new MenuScreen(startMenu));
        m_ScreenManager->add("game", new GameScreen());
        m_ScreenManager->add("pause", new PauseScreen(pauseMenu));
        m_ScreenManager->goTo("title");
    }

    virtual void onUpdate() override { m_ScreenManager->update(); }

    virtual void onDetach() override { m_ScreenManager->unload(); }
};

class MyApp : public Engine::Application {
  public:
    MyApp() {
        addLayer(new AppLayer());
        // addLayer(new Engine::ImGuiLayer());
    }

    virtual ~MyApp() {}
};

Engine::Application *Engine::createApplication() { return new MyApp(); }
