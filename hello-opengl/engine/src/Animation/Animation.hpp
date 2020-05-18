#pragma once

namespace Engine {

enum class AnimationProperty {
    None = 0,
    X = 1,
    Y = 2,
    Scale = 3,
    Angle = 4,
};

struct AnimationStep {
    AnimationProperty property;
    float value;

    AnimationStep(AnimationProperty property, float value)
        : property(property), value(value) {}
};

struct Animation {
    AnimationProperty property = AnimationProperty::None;
    float time = 0.0;
    float targetValue = 0.0;
    float currentValue = 0.0;

    Animation(AnimationProperty property, float targetValue, float time)
        : property(property), targetValue(targetValue), time(time) {}
};

struct TimeLineGap : public Animation {
    TimeLineGap(float time) : Animation(AnimationProperty::None, 0.0, time) {}
};

} // namespace Engine