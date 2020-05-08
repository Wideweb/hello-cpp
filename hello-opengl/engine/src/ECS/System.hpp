#pragma once

#include "Entity.hpp"
#include "EntityManager.hpp"
#include <vector>

namespace Engine {

class System {
  public:
    virtual void exec(EntityManager &entities) = 0;
};

} // namespace Engine
