#pragma once

#include "System.hpp"

namespace Engine {

class MorphingSystem : public System {
  public:
    virtual void exec(EntityManager &entities) override;
};

} // namespace Engine
