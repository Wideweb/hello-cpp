#pragma once

#include "System.hpp"

namespace Engine {

class CameraSystem : public System {
  public:
    virtual void exec(EntityManager &entities) override;
};

} // namespace Engine
