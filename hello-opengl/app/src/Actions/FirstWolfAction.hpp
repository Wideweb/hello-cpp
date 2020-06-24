#pragma once

#include "ActionManager.hpp"

class FirstWolfAction : public Action {
  private:
    std::shared_ptr<Engine::Entity> m_Wolf;

  public:
    FirstWolfAction(int x, float delay) : Action(x, delay) {}

    virtual void init(Context *context) override {
        m_Wolf = context->getEntity("wolf");
    }

    virtual void exec() override {
        m_Wolf->isActive = true;
        m_Executed = true;
    }
};
