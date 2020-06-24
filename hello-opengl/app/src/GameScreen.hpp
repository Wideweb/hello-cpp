#pragma once

#include "Actions.hpp"
#include "Screen.hpp"
#include "WaterSurface.hpp"

#include "ECS.hpp"

#include <memory>

class GameScreen : public Screen {
  private:
    std::shared_ptr<Engine::Entity> m_Player;
    std::shared_ptr<Engine::Entity> m_FlashLight;

    WaterSurface<20> m_Water;

    bool m_FPressed = false;

    bool m_RainActive = false;

    ActionManager m_Actions;

  public:
    GameScreen();

    virtual void load(Context *context) override;
    virtual void update() override;
    virtual void unload(Context *context) override;
};