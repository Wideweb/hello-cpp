#include "Application.hpp"
#include <chrono>
#include <thread>

namespace Engine {

Application *Application::s_Instance = nullptr;

Application::Application() {
    m_Window = std::unique_ptr<Window>(Window::create());
    m_Render = std::unique_ptr<Render>(Render::create());

    initialize();

    s_Instance = this;
}

void Application::initialize() {
    m_Window->init({640, 420});
    m_Window->setMouseEventCallback(
        std::bind(&Application::onMouseEvent, this, std::placeholders::_1));
    m_Window->setWindowEventCallback(
        std::bind(&Application::onWindowEvent, this, std::placeholders::_1));
}

void Application::run() {
    while (m_Running) {
        m_Window->readInput();

        for (auto layer : m_LayerStack) {
            layer->onUpdate();
            layer->onRender();
        }

        m_Window->swapBuffers();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void Application::onMouseEvent(MouseEvent &e) {
    for (auto layer : m_LayerStack) {
        layer->onMouseEvent(e);
    }
}

void Application::onWindowEvent(WindowEvent &e) {
    for (auto layer : m_LayerStack) {
        layer->onWindowEvent(e);
    }

    if (e.type == EventType::WindowClosed) {
        m_Running = false;
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
