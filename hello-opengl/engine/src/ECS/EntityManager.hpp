#pragma once

#include "Entity.hpp"
#include <memory>
#include <vector>

namespace Engine {

class EntityManager {
  private:
    std::vector<std::shared_ptr<Entity>> m_Entities;

  public:
    std::shared_ptr<Entity> addEntity(const std::string name) {
        auto entity = std::shared_ptr<Entity>(new Entity(name));
        m_Entities.push_back(entity);
        return entity;
    }

    std::vector<std::shared_ptr<Entity>> &getAll() { return m_Entities; }
};

} // namespace Engine
