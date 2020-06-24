#pragma once

#include "ActionManager.hpp"

class StopRainAction : public Action {
  private:
    std::shared_ptr<Engine::Entity> m_Rain;

  public:
    StopRainAction(int x, float delay) : Action(x, delay) {}

    virtual void init(Context *context) override {
        m_Rain = context->getEntity("rain");
    }

    virtual void exec() override {
        m_Rain->isActive = false;
        m_Executed = true;
    }
};
