#pragma once

#include "Animation.hpp"
#include <vector>

namespace Engine {

class TimeLine {
  private:
    int m_AnimationIndex = 0;
    std::vector<Animation> m_Animaitions;
    float m_ElapsedTime = 0.0;
    float m_Step = 0.0;

  public:
    TimeLine(const std::vector<Animation> &animations)
        : m_Animaitions(animations) {}

    AnimationStep step(float deltaTime) {
        Animation &animation = getCurrent();

        m_ElapsedTime += deltaTime;
        if (m_ElapsedTime > animation.time) {
            next();
        }

        float t = m_ElapsedTime / animation.time;
        float value = animation.targetValue * t;

        m_Step = value - animation.currentValue;
        animation.currentValue = value;

        return AnimationStep(animation.property, m_Step);
    }

    Animation &getCurrent() { return m_Animaitions[m_AnimationIndex]; }

  private:
    void next() {
        Animation &animation = getCurrent();
        animation.currentValue = 0;

        m_ElapsedTime -= animation.time;
        m_Step = 0.0;
        m_AnimationIndex++;
        if (m_AnimationIndex == m_Animaitions.size()) {
            m_AnimationIndex = 0;
        }
    }
};

} // namespace Engine