#pragma once

#include "InterpolatedTriangleRender.hpp"
#include "Window.hpp"
#include <memory>

namespace Engine {

class Application {
  protected:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<InterpolatedTriangleRender> m_Render;
    Canvas m_Canvas;

    bool m_Running = true;

  public:
    Application();
    virtual ~Application();

    virtual void render() = 0;
    virtual void onMouseEvent(MouseEvent &e);
    virtual void onWindowEvent(WindowEvent &e);

    void run();
};

} // namespace Engine
