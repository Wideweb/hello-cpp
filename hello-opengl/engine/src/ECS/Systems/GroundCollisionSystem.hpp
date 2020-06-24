#pragma once

#include "CollisionDetection.hpp"
#include "System.hpp"

namespace Engine {

class GroundCollisionSystem : public System {
  private:
    CollisionDetection m_CollisionDetection;

  public:
    virtual void exec(EntityManager &entities) override;
};

} // namespace Engine
