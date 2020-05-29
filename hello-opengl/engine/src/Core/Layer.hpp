#pragma once

#include "EntityManager.hpp"
#include "Window.hpp"
#include <string>

namespace Engine {

class Layer {
  private:
    std::shared_ptr<EntityManager> m_EntityManager;

  public:
    Layer();
    virtual ~Layer() = default;

    std::shared_ptr<Entity> addEntity(const std::string &name);
    std::shared_ptr<Entity> getEntity(const std::string &name);
    EntityManager &getEntities();
    void clear();

    void load(const std::string &configPath);

    virtual void onAttach(){};
    virtual void onDetach(){};

    virtual void onUpdate(){};
    virtual void onRender(){};

    virtual void onMouseEvent(MouseEvent &e){};
    virtual void onWindowEvent(WindowEvent &e){};
};

} // namespace Engine