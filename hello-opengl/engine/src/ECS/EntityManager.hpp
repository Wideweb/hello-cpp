#pragma once

#include "Entity.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Engine {

class EntityManager {
  private:
    std::vector<std::shared_ptr<Entity>> m_Entities;
    std::map<std::string, std::shared_ptr<Entity>> m_EntitiesMap;

  public:
    std::shared_ptr<Entity> addEntity(const std::string name) {
        auto entity = std::shared_ptr<Entity>(new Entity(name));
        m_Entities.push_back(entity);
        m_EntitiesMap[name] = entity;
        return entity;
    }

    std::vector<std::shared_ptr<Entity>> &getAll() { return m_Entities; }

    std::shared_ptr<Entity> &get(const std::string name) {
        return m_EntitiesMap[name];
    }
};

} // namespace Engine
