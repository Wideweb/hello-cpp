#pragma once

#include "Entity.hpp"
#include <string>

namespace Engine {

class KeyboardControlComponent : public Component {
  public:
    std::string upKey;
    std::string downKey;
    std::string rightKey;
    std::string leftKey;
    std::string shootKey;

    KeyboardControlComponent(std::string upKey, std::string rightKey,
                             std::string downKey, std::string leftKey,
                             std::string shootKey) {}
};

} // namespace Engine