#pragma once

#include "CollisionComponent.hpp"
#include "CollisionDetection.hpp"
#include "LocationComponent.hpp"
#include "ObstacleComponent.hpp"
#include "SlopeComponent.hpp"
#include "System.hpp"
#include "VelocityComponent.hpp"

namespace Engine {

class CollisionSystem : public System {
  private:
    CollisionDetection m_CollisionDetection;

  public:
    virtual void exec(EntityManager &entities) override;
};

} // namespace Engine
