#pragma once

#include "Entity.hpp"
#include "Math.hpp"
#include <string>

namespace Engine {

struct BeginInteractionEvent {
    std::string subject;
    std::string object;
};

struct EndInteractionEvent {
    std::string subject;
    std::string object;
};

class InteractionComponent : public Component {
  public:
    float distance;
    std::string subject;

    InteractionComponent(std::string subject, int distance)
        : subject(subject), distance(distance) {}
};

} // namespace Engine