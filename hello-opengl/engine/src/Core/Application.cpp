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

    initialize();

    s_Instance = this;
}

void Application::initialize() {
    m_Window->init({600, 600});
    m_Window->setMouseEventCallback(
        std::bind(&Application::onMouseEvent, this, std::placeholders::_1));
    m_Window->setWindowEventCallback(
        std::bind(&Application::onWindowEvent, this, std::placeholders::_1));
}

void Application::run() {
    m_Render->setClearColor(0.0, 0.0, 0.0, 1.0);

    while (m_Running) {
        m_Window->readInput();
        m_Input->update();

        m_Render->clear();

        for (auto layer : m_LayerStack) {
            layer->onUpdate();
            m_SystemStack.exec(layer->getEntities());
        }

        m_Window->swapBuffers();
    }
}

void Application::onMouseEvent(MouseEvent &e) {
    for (auto layer : m_LayerStack) {
        layer->onMouseEvent(e);
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
