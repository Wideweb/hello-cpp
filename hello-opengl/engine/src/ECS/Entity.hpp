#pragma once

#include <map>
#include <memory>
#include <sstream>
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
    virtual void serialize(std::ostringstream &out) = 0;
};

class Entity {
  private:
    std::string m_Name;
    std::vector<std::shared_ptr<Component>> m_Components;
    std::map<const std::type_info *, std::shared_ptr<Component>> m_ComponentMap;

  public:
    bool isActive = true;

    Entity(const std::string name) : m_Name(name) {}
    virtual ~Entity() = default;

    template <typename T, typename... TArgs>
    std::shared_ptr<T> addComponent(TArgs &&... args) {
        if (m_Name == "little-boy") {
            float a = 1;
        }

        std::shared_ptr<T> component;
        component.reset(new T(std::forward<TArgs>(args)...));
        m_Components.push_back(component);
        m_ComponentMap[&typeid(*component)] = component;
        return component;
    }

    template <typename T> bool hasComponent() {
        return getComponent<T>() != nullptr;
    }

    template <typename T> std::shared_ptr<T> getComponent() {
        return std::static_pointer_cast<T>(m_ComponentMap[&typeid(T)]);
    }

    std::string &getName() { return m_Name; }
    void setName(const std::string &name) { m_Name = name; }

    void serialize(std::ostringstream &out) {
        out << "entity " << getName();
        out << std::endl;

        for (auto component : m_Components) {
            component->serialize(out);
        }
    }
};

} // namespace Engine
