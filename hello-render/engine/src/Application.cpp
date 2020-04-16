#include "Application.hpp"
#include <chrono>
#include <thread>

namespace Engine {

Application::Application() {
    m_Window = std::unique_ptr<Window>(new Window);
    m_Window->init({width, height, sizeof(Color) * 8, width * sizeof(Color)});
    m_Window->setEventCallback(
        std::bind(&Application::onMouseEvent, this, std::placeholders::_1));

    m_Render = std::unique_ptr<InterpolatedTriangleRender>(
        new InterpolatedTriangleRender(m_Canvas));
}

void Application::run() {
    while (m_Running) {
        m_Window->readInput();
        render();
        m_Window->draw(m_Canvas.data());
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void Application::onMouseEvent(MouseEvent &e) {}

void Application::onWindowEvent(WindowEvent &e) {}

Application::~Application() {}

} // namespace Engine
