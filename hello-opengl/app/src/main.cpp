#include "GameScreen.hpp"
#include "MenuScreen.hpp"
#include "ScreenManager.hpp"

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
        auto menu =
            new Menu({MenuItem("start", MenuItemLinkType::Screen, "game"),
                      MenuItem("exit", MenuItemLinkType::Exit)});

        m_ScreenManager.reset(new ScreenManager());
        m_ScreenManager->init(this);
        m_ScreenManager->add("menu", new MenuScreen(menu));
        m_ScreenManager->add("game", new GameScreen());
        m_ScreenManager->goTo("menu");
    }

    virtual void onUpdate() override { m_ScreenManager->update(); }

    virtual void onDetach() override { m_ScreenManager->unload(); }
};

class MyApp : public Engine::Application {
  public:
    MyApp() {
        addLayer(new AppLayer());
        addLayer(new Engine::ImGuiLayer());
    }

    virtual ~MyApp() {}
};

Engine::Application *Engine::createApplication() { return new MyApp(); }
