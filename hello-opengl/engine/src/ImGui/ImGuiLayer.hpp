#pragma once

#include "Layer.hpp"
#include "Shader.hpp"
#include "imgui/imgui.h"

namespace Engine {

class ImGuiLayer : public Layer {
  private:
    std::shared_ptr<Shader> m_Shader;

    float mouseOffsetX = 0;
    float mouseOffsetY = 0;

    std::string texture;
    std::string entityId;
    std::shared_ptr<Entity> entity;

  public:
    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate() override;
    virtual void onRender() override;

    virtual void onMouseEvent(MouseEvent &e) override;
    virtual void onWindowEvent(WindowEvent &e) override;

  private:
    void draw(ImDrawData *drawData);
};

} // namespace Engine