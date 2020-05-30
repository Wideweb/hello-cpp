#include "Menu.hpp"
#include "ScreenManager.hpp"

Menu::Menu(const std::vector<MenuItem> &items) { m_Items = items; }

void Menu::load(Context *context) {
    for (auto &item : m_Items) {
        item.load(context);
        item.setOnSelectEvent(
            std::bind(&Menu::onItemSelected, this, std::placeholders::_1));
    }
}

void Menu::onItemSelected(const MenuItem &item) {
    switch (item.type) {
    case MenuItemLinkType::Screen:
        ScreenManager::get().goTo(item.link);
        break;
    case MenuItemLinkType::Exit:
        Engine::Application::get().stop();
        break;
    default:
        break;
    }
}

void Menu::update() {
    for (auto &item : m_Items) {
        item.update();
    }
}

void Menu::unload(Context *context) {
    for (auto &item : m_Items) {
        item.unload(context);
    }
}