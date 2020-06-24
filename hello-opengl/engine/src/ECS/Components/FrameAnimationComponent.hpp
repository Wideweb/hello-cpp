#pragma once

#include "Entity.hpp"

#include <string>

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

    virtual void serialize(std::ostringstream &out) override {
        out << "frameAnimation ";
        out << m_Animaitions["wait"].y << " ";
        out << m_Animaitions["wait"].dx << " ";
        out << m_Animaitions["wait"].framesNumber << " ";
        out << m_Animaitions["wait"].frameTime << " ";
        out << m_Animaitions["move"].y << " ";
        out << m_Animaitions["move"].dx << " ";
        out << m_Animaitions["move"].framesNumber << " ";
        out << m_Animaitions["move"].frameTime;
        out << std::endl;
    }
};

} // namespace Engine