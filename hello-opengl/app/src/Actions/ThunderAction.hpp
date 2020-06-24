#pragma once

#include "ActionManager.hpp"

class ThunderAction : public Action {
  private:
    std::shared_ptr<Engine::Entity> m_Thunder;

    std::shared_ptr<Engine::Entity> m_Wolf1;
    std::shared_ptr<Engine::Entity> m_Wolf2;
    std::shared_ptr<Engine::Entity> m_Wolf3;

  public:
    ThunderAction(int x, float delay) : Action(x, delay) {}

    virtual void init(Context *context) override {
        m_Thunder = context->getEntity("thunder");

        m_Wolf1 = context->getEntity("wolf1");
        m_Wolf2 = context->getEntity("wolf2");
        m_Wolf3 = context->getEntity("wolf3");
    }

    virtual void exec() override {
        m_Thunder->getComponent<Engine::AnimationComponent>()->isActive = true;

        m_Wolf1->addComponent<Engine::DieComponent>();
        m_Wolf2->addComponent<Engine::DieComponent>();
        m_Wolf3->addComponent<Engine::DieComponent>();

        m_Executed = true;
    }
};
