#pragma once

#include "System.hpp"

namespace Engine {

class MoveSystem : public System {
  public:
    virtual void exec(EntityManager &entities) override;
};

} // namespace Engine
