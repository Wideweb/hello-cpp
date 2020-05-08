#pragma once

#include "EntityManager.hpp"
#include "Window.hpp"
#include <string>

namespace Engine {

class Layer {
  private:
    EntityManager m_EntityManager;

  public:
    std::shared_ptr<Entity> addEntity(std::string name);
    EntityManager &getEntities();

    virtual void onAttach(){};
    virtual void onDetach(){};

    virtual void onUpdate(){};
    virtual void onRender(){};

    virtual void onMouseEvent(MouseEvent &e){};
    virtual void onWindowEvent(WindowEvent &e){};
};

} // namespace Engine