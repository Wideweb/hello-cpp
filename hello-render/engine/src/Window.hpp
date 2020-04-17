#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <string>

namespace Engine {

enum class EventType { None = 0, MouseMoved, WindowClosed };

class MouseEvent {
  public:
    int x;
    int y;
    EventType type;

    MouseEvent(int x, int y, EventType type) : x(x), y(y), type(type) {}
};

class WindowEvent {
  public:
    EventType type;

    WindowEvent(EventType type) : type(type) {}
};

struct WindowProps {
    int width;
    int height;
    int depth;
    int pitch;
    int rmask = 0x000000ff;
    int gmask = 0x0000ff00;
    int bmask = 0x00ff0000;
    int amask = 0;
};

class Window {
    template <typename T> using EventCallbackFn = std::function<void(T &)>;

  private:
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
    WindowProps m_Props;
    EventCallbackFn<MouseEvent> m_mouseEventCallback;
    EventCallbackFn<WindowEvent> m_windowEventCallback;

  public:
    std::string init(const WindowProps &props);
    void setMouseEventCallback(const EventCallbackFn<MouseEvent> &callback);
    void setWindowEventCallback(const EventCallbackFn<WindowEvent> &callback);
    void readInput();
    bool draw(void *pixels);
    void shutDown();
};

} // namespace Engine
