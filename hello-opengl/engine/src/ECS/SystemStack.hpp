#pragma once

#include "System.hpp"
#include <vector>

namespace Engine {

class SystemStack {
  private:
    std::vector<System *> m_Systems;

  public:
    SystemStack();
    void exec(EntityManager &entities);
};

} // namespace Engine
