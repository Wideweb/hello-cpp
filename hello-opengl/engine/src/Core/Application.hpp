#pragma once

#include "Layer.hpp"
#include "Render.hpp"
#include "Window.hpp"
#include <memory>

namespace Engine {

class Application {
  private:
    static Application *s_Instance;

  protected:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Render> m_Render;
    std::vector<Layer *> m_LayerStack;
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
    Render &getRender() { return *m_Render; }

    static Application &get() { return *s_Instance; }
};

Application *createApplication();

} // namespace Engine
