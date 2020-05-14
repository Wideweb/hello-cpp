#pragma once

#include "System.hpp"

namespace Engine {

class InteractionSystem : public System {
  public:
    virtual void exec(EntityManager &entities) override;
};

} // namespace Engine
