#pragma once

#include "System.hpp"

namespace Engine {

class MoveSystem : public System {
  public:
    virtual void exec(std::vector<std::shared_ptr<Entity>> &entities) override;
};

} // namespace Engine
