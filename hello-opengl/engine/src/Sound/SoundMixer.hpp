#pragma once

#include "SoundBuffer.hpp"
#include <string>

namespace Engine {

class SoundMixer {
  public:
    virtual ~SoundMixer() = default;

    virtual void init() = 0;

    static SoundMixer *create();

    virtual void add(std::string name, std::string path) = 0;
    virtual void play(std::string name, float volume,
                      SoundBuffer::Properties properties) = 0;
    virtual void stop(std::string name) = 0;
    virtual void stop() = 0;
    virtual void clear() = 0;
};

} // namespace Engine