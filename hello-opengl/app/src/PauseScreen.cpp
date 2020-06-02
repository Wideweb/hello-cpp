#include "PauseScreen.hpp"
#include "ScreenManager.hpp"

PauseScreen::PauseScreen(Menu *menu) { m_Menu.reset(menu); }

void PauseScreen::load(Context *context) {
    context->load("./config/pause-menu.txt");
    m_Menu->load(context);
}

void PauseScreen::update() { m_Menu->update(); }

void PauseScreen::unload(Context *context) {
    m_Menu->unload(context);
    context->clear();
}