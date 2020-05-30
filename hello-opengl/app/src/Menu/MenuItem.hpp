#pragma once

#include "App.hpp"

#include <functional>
#include <string>

enum class MenuItemLinkType {
    Screen = 0,
    Exit = 1,
};

class MenuItem {
  private:
    std::string m_EnityId;
    std::shared_ptr<Engine::Entity> m_Entity;
    std::function<void(MenuItem &)> m_onSelect;

  public:
    MenuItemLinkType type;
    std::string link;

    MenuItem(const std::string &enityId, MenuItemLinkType type,
             std::string link = "");

    void load(Context *);
    void update();
    void unload(Context *);

    void setOnSelectEvent(std::function<void(const MenuItem &)> callback);

  private:
    void onMouseIn();
    void onMouseOut();
};