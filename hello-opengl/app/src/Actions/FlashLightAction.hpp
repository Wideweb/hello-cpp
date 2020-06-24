#pragma once

#include "ActionManager.hpp"

class TurnOffFlashLightAction : public Action {
  private:
    std::shared_ptr<Engine::Entity> m_Player;
    std::shared_ptr<Engine::Entity> m_FlashLight;

  public:
    TurnOffFlashLightAction(int x, float delay) : Action(x, delay) {}

    virtual void init(Context *context) override {
        m_Player = context->getEntity("player");
        m_FlashLight = context->getEntity("player-flashlight");
    }

    virtual void exec() override {
        m_Player->getComponent<Engine::AttackComponent>()->isActive = false;
        m_FlashLight->getComponent<Engine::AnimationComponent>()->isActive =
            true;
        m_Executed = true;
    }
};
