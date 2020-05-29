#pragma once

#include "App.hpp"
#include "Screen.hpp"

class MenuScreen : public Screen {
  private:
    std::shared_ptr<Engine::Entity> m_Start;
    std::shared_ptr<Engine::Entity> m_Exit;

  public:
    MenuScreen();

    virtual void load(Context *context) override;
    virtual void update() override;
    virtual void unload(Context *context) override;
};