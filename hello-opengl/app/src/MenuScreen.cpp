#include "MenuScreen.hpp"
#include "ScreenManager.hpp"

MenuScreen::MenuScreen() {}

void MenuScreen::load(Context *context) {
    context->load("./config/menu.txt");
    m_Start = context->getEntity("start");
    m_Exit = context->getEntity("exit");
}

void MenuScreen::update() {
    auto &input = Engine::Application::get().getInput();

    if (input.IsMousePressed(Engine::MouseButton::Left)) {
        Engine::Vec2 pos = input.GetMousePosition();
        {
            auto location = m_Start->getComponent<Engine::LocationComponent>();
            auto texture = m_Start->getComponent<Engine::TextureComponent>();
            int left = location->x - texture->width / 2;
            int right = location->x + texture->width / 2;
            int top = location->y + texture->height / 2;
            int bottom = location->y - texture->height / 2;

            if (left < pos.x && right > pos.x && top > pos.y &&
                bottom < pos.y) {
                ScreenManager::get().goTo("game");
            }
        }
    }
}

void MenuScreen::unload(Context *context) { context->clear(); }