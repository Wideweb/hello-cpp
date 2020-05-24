#pragma once

#include "AnimationScene.hpp"
#include "EntityManager.hpp"
#include <memory>
#include <string>

namespace Engine {

class Loader {
  private:
    std::shared_ptr<EntityManager> m_EntityManager;

  public:
    Loader(std::shared_ptr<EntityManager> entityManager);
    ~Loader();

    void load(const std::string &path);

  private:
    void loadEntities(const std::string &path);
    AnimationScene loadAnimation(const std::string &path);
};

} // namespace Engine