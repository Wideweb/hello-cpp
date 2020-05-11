#pragma once

#include "Buffer.hpp"
#include "Entity.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include <map>
#include <string>
#include <vector>

namespace Engine {

class Animation {
  public:
    int framesNumber;
    float frameTime;

    float dx;
    float y;

    Animation() {}
    Animation(float y, float dx, int framesNumber, float time)
        : y(y), dx(dx), framesNumber(framesNumber) {
        frameTime = time / framesNumber;
    }
};

class AnimationComponent : public Component {
  public:
    int frameIndex = 0;
    float frameElapsedTime = 0.0;

    std::string animationId;
    std::map<std::string, Animation> animaitions;

    AnimationComponent(const Animation &wait, const Animation &move) {
        animaitions["wait"] = wait;
        animaitions["move"] = move;
        animationId = "wait";
    }

    Animation &getCurrent() { return animaitions[animationId]; }
};

} // namespace Engine