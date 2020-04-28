#pragma once

#include "Camera.hpp"
#include "Input.hpp"
#include "Layer.hpp"
#include "Render.hpp"
#include "SystemStack.hpp"
#include "Window.hpp"
#include <memory>

namespace Engine {

class Application {
  private:
    static Application *s_Instance;

    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Input> m_Input;
    std::unique_ptr<Render> m_Render;
    std::unique_ptr<Camera> m_Camera;
    std::vector<Layer *> m_LayerStack;
    SystemStack m_SystemStack;

    bool m_Running = true;

  public:
    Application();
    virtual ~Application();

    void onMouseEvent(MouseEvent &e);
    void onWindowEvent(WindowEvent &e);

    void initialize();
    void run();

    void addLayer(Layer *layer);

    Window &getWindow() { return *m_Window; }
    Input &getInput() { return *m_Input; }
    Render &getRender() { return *m_Render; }
    Camera &getCamera() { return *m_Camera; }

    static Application &get() { return *s_Instance; }
};

Application *createApplication();

} // namespace Engine
