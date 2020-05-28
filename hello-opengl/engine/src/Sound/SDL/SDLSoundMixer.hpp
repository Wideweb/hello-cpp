#pragma once

#include "SDLSoundBuffer.hpp"
#include "SoundMixer.hpp"
#include <SDL.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Engine {

class SDLSoundMixer : public SoundMixer {
  private:
    SDL_AudioDeviceID m_Device;
    SDL_AudioSpec m_DeviceSpec;

    std::vector<std::shared_ptr<SDLSoundBuffer>> m_Sounds;
    std::map<std::string, std::shared_ptr<SDLSoundBuffer>> m_SoundsMap;

  public:
    SDLSoundMixer();

    virtual void add(std::string name, std::string path) override;
    virtual void play(std::string name) override;

    static void audioCallback(void *, uint8_t *, int);
};

} // namespace Engine