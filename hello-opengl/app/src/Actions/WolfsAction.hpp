#pragma once

#include "ActionManager.hpp"

class WolfsAction : public Action {
  private:
    std::shared_ptr<Engine::Entity> m_Wolf1;
    std::shared_ptr<Engine::Entity> m_Wolf2;
    std::shared_ptr<Engine::Entity> m_Wolf3;

  public:
    WolfsAction(int x, float delay) : Action(x, delay) {}

    virtual void init(Context *context) override {
        m_Wolf1 = context->getEntity("wolf1");
        m_Wolf2 = context->getEntity("wolf2");
        m_Wolf3 = context->getEntity("wolf3");
    }

    virtual void exec() override {
        m_Wolf1->isActive = true;
        m_Wolf2->isActive = true;
        m_Wolf3->isActive = true;
        m_Executed = true;
    }
};
