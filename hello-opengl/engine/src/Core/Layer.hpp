#pragma once

#include "Window.hpp"

namespace Engine {

class Layer {
  public:
    virtual void onAttach(){};
    virtual void onDetach(){};

    virtual void onUpdate(){};
    virtual void onRender(){};

    virtual void onMouseEvent(MouseEvent &e){};
    virtual void onWindowEvent(WindowEvent &e){};
};

} // namespace Engine