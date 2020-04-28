#pragma once

#include "Entity.hpp"
#include <vector>

namespace Engine {

class System {
  public:
    virtual void exec(std::vector<std::shared_ptr<Entity>> &entities) = 0;
};

} // namespace Engine
