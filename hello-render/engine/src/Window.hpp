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
    using EventCallbackFn = std::function<void(MouseEvent &)>;

  private:
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
    WindowProps m_Props;
    EventCallbackFn m_eventCallback;

  public:
    std::string init(const WindowProps &props);
    void setEventCallback(const EventCallbackFn &callback);
    void readInput();
    bool draw(void *pixels);
    void shutDown();
};

} // namespace Engine
