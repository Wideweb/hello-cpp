#pragma once

#include "Camera.hpp"
#include "EventHandler.hpp"
#include "Input.hpp"
#include "Layer.hpp"
#include "Render.hpp"
#include "ShaderManager.hpp"
#include "SoundMixer.hpp"
#include "SystemStack.hpp"
#include "TextureManager.hpp"
#include "Time.hpp"
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
    std::unique_ptr<TextureManager> m_Texture;
    std::unique_ptr<ShaderManager> m_Shades;
    std::unique_ptr<EventHandler> m_EventHandler;
    std::unique_ptr<SoundMixer> m_Sound;
    std::vector<Layer *> m_LayerStack;
    SystemStack m_SystemStack;
    Time m_Time;

    bool m_Running = true;

  public:
    Application();
    virtual ~Application();

    void onMouseEvent(MouseEvent &e);
    void onWindowEvent(WindowEvent &e);

    void initialize();
    void run();
    void stop();

    void addLayer(Layer *layer);

    Window &getWindow() { return *m_Window; }
    SoundMixer &getSound() { return *m_Sound; }
    Input &getInput() { return *m_Input; }
    Render &getRender() { return *m_Render; }
    Camera &getCamera() { return *m_Camera; }
    Time &getTime() { return m_Time; }
    TextureManager &getTextures() { return *m_Texture; }
    ShaderManager &getShaders() { return *m_Shades; }
    EventHandler &getEventHandler() { return *m_EventHandler; }
    std::vector<Layer *> &getLayers() { return m_LayerStack; }
    Vec2 getScreenFix();

    static Application &get() { return *s_Instance; }
};

Application *createApplication();

} // namespace Engine
