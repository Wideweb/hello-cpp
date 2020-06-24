#pragma once

#include "System.hpp"

namespace Engine {

class AttackSystem : public System {
  public:
    virtual void exec(EntityManager &entities) override;
};

} // namespace Engine
