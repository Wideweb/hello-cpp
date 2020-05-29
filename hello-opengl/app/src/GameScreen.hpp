#pragma once

#include "Screen.hpp"

#include "ECS.hpp"

#include <memory>

class GameScreen : public Screen {
  private:
    std::shared_ptr<Engine::Entity> m_Player;

  public:
    GameScreen();

    virtual void load(Context *context) override;
    virtual void update() override;
    virtual void unload(Context *context) override;
};