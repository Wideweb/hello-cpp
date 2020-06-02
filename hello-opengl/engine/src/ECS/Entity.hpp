#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Engine {

class Entity;

class Component {
  protected:
    std::shared_ptr<Entity> m_Entity;

  public:
    bool isActive = true;

    virtual ~Component() = default;
    const Entity &getOwner() const { return *m_Entity; }
};

class Entity {
  private:
    std::string m_Name;
    std::vector<std::shared_ptr<Component>> m_Components;
    std::map<const std::type_info *, std::shared_ptr<Component>> m_ComponentMap;

  public:
    Entity(const std::string name) : m_Name(name) {}
    virtual ~Entity() = default;

    template <typename T, typename... TArgs>
    std::shared_ptr<T> addComponent(TArgs &&... args) {
        std::shared_ptr<T> component;
        component.reset(new T(std::forward<TArgs>(args)...));
        m_Components.push_back(component);
        m_ComponentMap[&typeid(*component)] = component;
        return component;
    }

    template <typename T> bool hasComponent() const {
        return m_ComponentMap.count(&typeid(T));
    }

    template <typename T> std::shared_ptr<T> getComponent() {
        return std::static_pointer_cast<T>(m_ComponentMap[&typeid(T)]);
    }

    std::string &getName() { return m_Name; }
};

} // namespace Engine
