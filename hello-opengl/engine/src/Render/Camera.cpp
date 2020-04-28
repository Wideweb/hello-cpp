#include "Camera.hpp"

namespace Engine {

void Camera::setPosition(float _x, float _y) {
    x = _x;
    y = _y;
    m_ViewMatrix = {1.0f, 0.0f, 0.0f, 0.0f,

                    0.0f, 1.0f, 0.0f, 0.0f,

                    0.0f, 0.0f, 1.0f, 0.0f,

                    _x,   _y,   0.0f, 1.0f};
}

std::vector<float> &Camera::getViewMatrix() { return m_ViewMatrix; }

} // namespace Engine
