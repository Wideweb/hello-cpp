#include "ScreenManager.hpp"

ScreenManager *ScreenManager::s_Instance = nullptr;

ScreenManager::ScreenManager() { s_Instance = this; }

ScreenManager::~ScreenManager() {}

void ScreenManager::init(Context *context) { m_Context = context; }

void ScreenManager::add(const std::string &screenId, Screen *screen) {
    std::shared_ptr<Screen> ptr(screen);
    m_ScreenMap[screenId] = ptr;
}

void ScreenManager::goTo(const std::string &screenId) {
    if (m_IsTransitioning) {
        return;
    }
    m_IsTransitioning = true;
    m_New = m_ScreenMap[screenId];
}

void ScreenManager::update() {
    if (m_IsTransitioning) {
        m_IsTransitioning = false;

        if (m_Current) {
            m_Current->unload(m_Context);
        }

        auto &render = Engine::Application::get().getRender();
        render.setClearColor(0.0, 0.1, 0.1, 1.0);
        render.clear();
        Engine::Application::get().getWindow().swapBuffers();
        render.clear();

        Engine::Application::get().getCamera().setPosition(0, 0);

        m_New->load(m_Context);
        m_Current = m_New;

        render.setClearColor(0.0, 0.1, 0.1, 1.0);
    }

    if (m_Current) {
        m_Current->update();
    }
}

void ScreenManager::unload() {
    if (m_Current) {
        m_Current->unload(m_Context);
    }
}
