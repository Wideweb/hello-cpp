#pragma once

#include "Entity.hpp"

#include <string>

namespace Engine {

class FrameComponent : public Component {
  public:
    int index = 0;
    int framesNumber;

    FrameComponent(int framesNumber) : framesNumber(framesNumber) {}

    void next(std::string animationId) {
        index++;
        if (index == framesNumber) {
            index = 0;
        }
    }

    virtual void serialize(std::ostringstream &out) override {
        out << "frame ";
        out << framesNumber;
        out << std::endl;
    }
};

} // namespace Engine