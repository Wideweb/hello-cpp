#pragma once

#include "ActionManager.hpp"

#include <cmath>

class GrandSun : public Action {
  private:
    std::shared_ptr<Engine::Entity> m_Sun;

  public:
    GrandSun() : Action(0, 0) {}

    virtual void init(Context *context) override {
        m_Sun = context->getEntity("grand-sun");
    }

    virtual void exec() override {
        m_Executed = true;
        m_Sun->getComponent<Engine::AnimationComponent>()->isActive = true;
    }
};
