#pragma once

#include "App.hpp"

#include <string>
#include <vector>

class Action {
  protected:
    bool m_Executed = false;
    bool m_Reached = false;
    int m_X;
    float m_Delay;
    float m_ElapsedTime = 0;
    std::vector<Action *> m_Actions;

  public:
    Action(int x, float delay) : m_X(x), m_Delay(delay) {}
    virtual ~Action() {
        for (auto action : m_Actions) {
            delete action;
        }
    }

    virtual void init(Context *context) {}

    virtual bool isReady(std::shared_ptr<Engine::Entity> player) {
        if (m_Executed) {
            return false;
        }

        if (!m_Reached) {
            auto location = player->getComponent<Engine::LocationComponent>();
            m_Reached = location->x > m_X;
        }

        if (!m_Reached) {
            return false;
        }

        if (m_ElapsedTime >= m_Delay) {
            return true;
        }

        m_ElapsedTime += Engine::Application::get().getTime().getDeltaSeconds();
        return false;
    };

    virtual void exec() = 0;

    Action *then(Action *action) {
        m_Actions.push_back(action);
        return this;
    }

    std::vector<Action *> &getSubActions() { return m_Actions; }
};

class ActionManager {
  private:
    std::vector<Action *> m_Actions;
    std::shared_ptr<Engine::Entity> m_Player;

  public:
    ActionManager() {}
    virtual ~ActionManager() {
        for (auto action : m_Actions) {
            delete action;
        }
    }

    void init(Context *context) {
        m_Player = context->getEntity("player");
        for (auto action : m_Actions) {
            action->init(context);

            for (auto subAction : action->getSubActions()) {
                subAction->init(context);
            }
        }
    }

    Action *add(Action *action) {
        m_Actions.push_back(action);
        return action;
    }

    void update() {
        for (auto action : m_Actions) {
            if (action->isReady(m_Player)) {
                action->exec();

                for (auto subAction : action->getSubActions()) {
                    subAction->exec();
                }
            }
        }
    }
};
