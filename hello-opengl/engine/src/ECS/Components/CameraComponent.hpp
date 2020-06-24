#pragma once

#include "Entity.hpp"

namespace Engine {

class CameraComponent : public Component {
  public:
    int leftBound;
    int rightBound;
    int offset;
    CameraComponent(int leftBound, int rightBound, int offset)
        : leftBound(leftBound), rightBound(rightBound), offset(offset) {}

    virtual void serialize(std::ostringstream &out) override {
        out << "camera"
            << " ";
        out << leftBound << " ";
        out << rightBound << " ";
        out << offset;
        out << std::endl;
    }
};

} // namespace Engine