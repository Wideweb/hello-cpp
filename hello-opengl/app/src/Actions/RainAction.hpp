#pragma once

#include "ActionManager.hpp"

class RainAction : public Action {
  private:
    std::shared_ptr<Engine::Entity> m_Rain;

  public:
    RainAction(int x, float delay) : Action(x, delay) {}

    virtual void init(Context *context) override {
        m_Rain = context->getEntity("rain");
    }

    virtual void exec() override {
        m_Rain->isActive = true;
        m_Executed = true;
    }
};
