#pragma once

#include "ActionManager.hpp"

class TakeLighterAction : public Action {
  private:
    std::shared_ptr<Engine::Entity> m_Lighter;
    std::shared_ptr<Engine::Entity> m_Player;
    std::shared_ptr<Engine::Entity> m_PlayerLighter;

  public:
    TakeLighterAction(int x, float delay) : Action(x, delay) {}

    virtual void init(Context *context) override {
        m_Player = context->getEntity("player");
        m_Lighter = context->getEntity("flashlight");
        m_PlayerLighter = context->getEntity("player-flashlight");
    }

    virtual void exec() override {
        m_Lighter->isActive = false;
        m_PlayerLighter->isActive = true;
        m_Player->getComponent<Engine::AttackComponent>()->isActive = true;
        m_Executed = true;
    }
};
