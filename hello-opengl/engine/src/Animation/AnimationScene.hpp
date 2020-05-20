#pragma once

#include "TimeLine.hpp"
#include <vector>

namespace Engine {

class AnimationScene {
  private:
    std::vector<TimeLine> m_TimeLines;

  public:
    AnimationScene() {}
    AnimationScene(const std::vector<TimeLine> &timeLines)
        : m_TimeLines(timeLines) {}

    void add(const TimeLine &timeLine) { m_TimeLines.push_back(timeLine); }

    std::vector<AnimationStep> step(float deltaTime) {
        std::vector<AnimationStep> steps;

        for (TimeLine &timeLine : m_TimeLines) {
            steps.push_back(timeLine.step(deltaTime));
        }

        return steps;
    }
};

} // namespace Engine