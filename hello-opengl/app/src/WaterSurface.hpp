#pragma once

#include <array>

class WaterSurfaceParticle {
  private:
    float m_TargetHeight = 50;

  public:
    float position;
    float velocity;
    float height;

    void update(float dampening, float tension) {
        float x = height - m_TargetHeight;
        float acceleration = -tension * x - dampening * velocity;

        position += velocity;
        velocity += acceleration;
    }
};

template <size_t N> class WaterSurface {
  private:
    std::array<WaterSurfaceParticle, N> m_Springs;
    std::array<float, N> m_LeftDeltas;
    std::array<float, N> m_RightDeltas;

    float m_Spread = 0.2;
    float m_Dampening = 0.2;
    float m_Tension = 0.025;

  public:
    WaterSurface() {
        m_LeftDeltas.fill(0);
        m_RightDeltas.fill(0);
    }

    void update() {
        for (int i = 0; i < N; i++) {
            m_Springs[i].update(m_Dampening, m_Tension);
        }

        for (int j = 0; j < 8; j++) {
            for (int i = 0; i < N; i++) {
                if (i > 0) {
                    float dh = m_Springs[i].height - m_Springs[i - 1].height;
                    m_LeftDeltas[i] = m_Spread * dh;
                    m_Springs[i - 1].velocity += m_LeftDeltas[i];
                }
                if (i < N - 1) {
                    float dh = m_Springs[i].height - m_Springs[i + 1].height;
                    m_RightDeltas[i] = m_Spread * dh;
                    m_Springs[i + 1].velocity += m_RightDeltas[i];
                }
            }

            for (int i = 0; i < N; i++) {
                if (i > 0)
                    m_Springs[i - 1].height += m_LeftDeltas[i];
                if (i < N - 1)
                    m_Springs[i + 1].height += m_RightDeltas[i];
            }
        }
    }
};