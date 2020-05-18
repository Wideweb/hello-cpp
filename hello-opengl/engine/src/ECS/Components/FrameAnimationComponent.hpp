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

class FrameAnimation {
  public:
    int framesNumber;
    float frameTime;

    float dx;
    float y;

    FrameAnimation() {}
    FrameAnimation(float y, float dx, int framesNumber, float time)
        : y(y), dx(dx), framesNumber(framesNumber) {
        frameTime = time / framesNumber;
    }
};

class FrameAnimationComponent : public Component {
  private:
    std::string m_AnimationId;
    std::map<std::string, FrameAnimation> m_Animaitions;

  public:
    int frameIndex = 0;
    float frameElapsedTime = 0.0;

    FrameAnimationComponent(const FrameAnimation &wait,
                            const FrameAnimation &move) {
        m_Animaitions["wait"] = wait;
        m_Animaitions["move"] = move;
        m_AnimationId = "wait";
    }

    void play(std::string animationId) {
        if (m_AnimationId != animationId) {
            frameIndex = 0;
            frameElapsedTime = 0;
            m_AnimationId = animationId;
        }
    }

    FrameAnimation &getCurrent() { return m_Animaitions[m_AnimationId]; }
};

} // namespace Engine