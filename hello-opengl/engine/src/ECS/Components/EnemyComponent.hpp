#pragma once

#include "Entity.hpp"

namespace Engine {

class EnemyComponent : public Component {
  public:
    EnemyComponent() {}

    virtual void serialize(std::ostringstream &out) override {
        out << "enemy" << std::endl;
    }
};

} // namespace Engine