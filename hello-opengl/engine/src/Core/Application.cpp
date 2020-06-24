#include "Application.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

namespace Engine {

Application *Application::s_Instance = nullptr;

Application::Application() {
    m_Window = std::unique_ptr<Window>(Window::create());
    m_Input = std::unique_ptr<Input>(Input::create());
    m_Render = std::unique_ptr<Render>(Render::create());
    m_Camera = std::unique_ptr<Camera>(new Camera());
    m_Texture = std::unique_ptr<TextureManager>(new TextureManager());
    m_Shades = std::unique_ptr<ShaderManager>(new ShaderManager());
    m_EventHandler = std::unique_ptr<EventHandler>(new EventHandler());
    m_Sound = std::unique_ptr<SoundMixer>(SoundMixer::create());

    initialize();

    s_Instance = this;
}

void Application::initialize() {
    m_Window->init({960, 540});
    m_Window->setMouseEventCallback(
        std::bind(&Application::onMouseEvent, this, std::placeholders::_1));
    m_Window->setWindowEventCallback(
        std::bind(&Application::onWindowEvent, this, std::placeholders::_1));
    m_Sound->init();
    m_Time.init();
}

Vec2 Application::getScreenFix() {
    return Vec2(960.0 / m_Window->getWidth(), 540.0 / m_Window->getHeight());
}

void Application::run() {
    m_Render->setClearColor(0.0, 0.1, 0.1, 1.0);
    m_Time.tick();

    while (m_Running) {
        m_Time.tick();

        m_Window->readInput();
        m_Input->update();

        m_Render->clear();

        for (auto layer : m_LayerStack) {
            layer->onUpdate();
            if (!layer->getEntities().empty()) {
                m_SystemStack.exec(layer->getEntities());
            }
            layer->onRender();
        }

        m_Window->swapBuffers();
    }
}

void Application::stop() { m_Running = false; }

void Application::onMouseEvent(MouseEvent &e) {
    for (size_t i = m_LayerStack.size() - 1; i > 0; i--) {
        auto layer = m_LayerStack[i];
        layer->onMouseEvent(e);
        if (e.handled) {
            break;
        }
    }
}

void Application::onWindowEvent(WindowEvent &e) {
    if (e.type == EventType::WindowResized) {
        m_Render->setViewport(m_Window->getWidth(), m_Window->getHeight());
    }

    for (auto layer : m_LayerStack) {
        layer->onWindowEvent(e);
    }

    if (e.type == EventType::WindowClosed) {
        stop();
    }
}

void Application::addLayer(Layer *layer) {
    m_LayerStack.push_back(layer);
    layer->onAttach();
}

Application::~Application() {
    for (auto layer : m_LayerStack) {
        layer->onDetach();
    }
    m_Window->shutDown();
}

} // namespace Engine
