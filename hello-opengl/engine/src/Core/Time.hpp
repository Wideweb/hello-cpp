#pragma once

namespace Engine {

class Time {
  private:
    float m_deltaTime = 0;
    float m_LastFrameTime = 0;

  public:
    void init();
    void tick();
    float getDelta() const;
};

} // namespace Engine