#pragma once

#include <vector>

namespace Engine {

class Camera {
  private:
    std::vector<float> m_ViewMatrix;

  public:
    float x;
    float y;

    virtual ~Camera() = default;
    void setPosition(float x, float y);
    std::vector<float> &getViewMatrix();
};

} // namespace Engine
