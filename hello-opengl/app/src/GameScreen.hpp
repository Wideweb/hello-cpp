#pragma once

#include "Screen.hpp"

#include "ECS.hpp"

#include <memory>

class GameScreen : public Screen {
  private:
    std::shared_ptr<Engine::Entity> m_Player;
    std::shared_ptr<Engine::Entity> m_FlashLight;
    bool m_FPressed = false;

  public:
    GameScreen();

    virtual void load(Context *context) override;
    virtual void update() override;
    virtual void unload(Context *context) override;
};