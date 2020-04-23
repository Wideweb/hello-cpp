#pragma once

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
};

class Window {
  public:
    template <typename T> using EventCallbackFn = std::function<void(T &)>;

    virtual ~Window();

    virtual void init(const WindowProps &props) = 0;

    virtual void
    setMouseEventCallback(const EventCallbackFn<MouseEvent> &callback) = 0;
    virtual void
    setWindowEventCallback(const EventCallbackFn<WindowEvent> &callback) = 0;

    virtual void readInput() = 0;
    virtual void swapBuffers() = 0;
    virtual void shutDown() = 0;
    virtual void *getNaviteWindow() const = 0;

    static Window *create();
};

} // namespace Engine
