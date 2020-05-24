#pragma once

#include "SoundBuffer.hpp"
#include <string>

namespace Engine {

class SoundMixer {
  public:
    virtual ~SoundMixer() = default;

    static SoundMixer *create();

    virtual void add(std::string name, std::string path) = 0;
    virtual void play(std::string name) = 0;
};

} // namespace Engine