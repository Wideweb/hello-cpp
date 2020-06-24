#pragma once

#include "AnimationScene.hpp"
#include "Entity.hpp"

namespace Engine {

class AnimationComponent : public Component {
  public:
    AnimationScene scene;

    AnimationComponent(const AnimationScene &scene) : scene(scene) {}

    virtual void serialize(std::ostringstream &out) override {}
};

} // namespace Engine