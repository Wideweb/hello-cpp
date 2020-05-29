#include "ScreenManager.hpp"

ScreenManager *ScreenManager::s_Instance = nullptr;

ScreenManager::ScreenManager() { s_Instance = this; }

ScreenManager::~ScreenManager() {}

void ScreenManager::init(Context *context) { m_Context = context; }

void ScreenManager::add(std::string screenId, Screen *screen) {
    std::shared_ptr<Screen> ptr(screen);
    m_ScreenMap[screenId] = ptr;
}

void ScreenManager::goTo(std::string screenId) {
    auto newScreen = m_ScreenMap[screenId];

    if (m_Current) {
        m_Current->unload(m_Context);
    }

    newScreen->load(m_Context);
    m_Current = newScreen;
}

void ScreenManager::update() {
    if (m_Current) {
        m_Current->update();
    }
}

void ScreenManager::unload() {
    if (m_Current) {
        m_Current->unload(m_Context);
    }
}
