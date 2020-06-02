#pragma once

#include "App.hpp"
#include "Menu.hpp"
#include "Screen.hpp"

class PauseScreen : public Screen {
  private:
    std::shared_ptr<Menu> m_Menu;

  public:
    PauseScreen(Menu *menu);

    virtual void load(Context *context) override;
    virtual void update() override;
    virtual void unload(Context *context) override;
};