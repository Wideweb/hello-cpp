#pragma once

#include "ActionManager.hpp"

class WolfIsGone : public Action {
  private:
    std::shared_ptr<Engine::Entity> m_Wolf;

  public:
    WolfIsGone() : Action(0, 0) {}

    virtual void init(Context *context) override {
        m_Wolf = context->getEntity("wolf");
    }

    virtual bool isReady(std::shared_ptr<Engine::Entity> player) override {
        if (m_Executed) {
            return false;
        }

        if (!m_Wolf->isActive) {
            return false;
        }

        if (m_Wolf->hasComponent<Engine::RunningAwayComponent>()) {
            return true;
        }

        return false;
    }

    virtual void exec() override { m_Executed = true; }
};
