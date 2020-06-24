#include "TitleScreen.hpp"
#include "ScreenManager.hpp"

TitleScreen::TitleScreen() {}

void TitleScreen::load(Context *context) {
    context->load("./config/title.txt");
}

void TitleScreen::update() {
    m_Elapsed += Engine::Application::get().getTime().getDeltaSeconds();

    if (m_Elapsed > 4.0) {
        ScreenManager::get().goTo("menu");
    }
}

void TitleScreen::unload(Context *context) { context->clear(); }