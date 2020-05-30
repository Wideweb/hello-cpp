#include "MenuScreen.hpp"
#include "ScreenManager.hpp"

MenuScreen::MenuScreen(Menu *menu) { m_Menu.reset(menu); }

void MenuScreen::load(Context *context) {
    context->load("./config/menu.txt");
    m_Menu->load(context);
}

void MenuScreen::update() { m_Menu->update(); }

void MenuScreen::unload(Context *context) {
    m_Menu->unload(context);
    context->clear();
}