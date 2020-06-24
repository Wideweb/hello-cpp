#pragma once

#include "Entity.hpp"

namespace Engine {

class EmitterComponent : public Component {
  public:
    std::string entity;
    int counter = 0;
    float elapsedTime = 0;
    float interval = 0.05;
    int bufferSize = 200;
    int index = 0;
    int width;

    EmitterComponent(const std::string &entity, int buffer, int width,
                     float interval)
        : entity(entity), bufferSize(buffer), width(width), interval(interval) {
    }

    virtual void serialize(std::ostringstream &out) override {
        out << "emitter ";
        out << entity << " ";
        out << bufferSize << " ";
        out << width << " ";
        out << interval << " ";
        out << std::endl;
    }
};

} // namespace Engine