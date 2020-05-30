#pragma once

#include "App.hpp"
#include "Menu.hpp"
#include "Screen.hpp"

class MenuScreen : public Screen {
  private:
    std::shared_ptr<Menu> m_Menu;

  public:
    MenuScreen(Menu *menu);

    virtual void load(Context *context) override;
    virtual void update() override;
    virtual void unload(Context *context) override;
};