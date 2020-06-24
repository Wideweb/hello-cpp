#pragma once

#include "ECS.hpp"

#include <sstream>
#include <string>

namespace Engine {

class EntitySerializer {
  public:
    static Entity *from(std::istringstream &in);
};

} // namespace Engine