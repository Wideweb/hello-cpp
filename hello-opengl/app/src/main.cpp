#include "GameScreen.hpp"
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
        m_ScreenManager.reset(new ScreenManager());
        m_ScreenManager->init(this);
        m_ScreenManager->add("game", new GameScreen());
        m_ScreenManager->goTo("game");
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
