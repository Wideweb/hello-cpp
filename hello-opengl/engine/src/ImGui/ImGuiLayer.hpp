#pragma once

#include "Layer.hpp"

namespace Engine {

class ImGuiLayer : public Layer {
  public:
    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate() override;
    virtual void onRender() override;

    virtual void onMouseEvent(MouseEvent &e) override;
    virtual void onWindowEvent(WindowEvent &e) override;
};

} // namespace Engine