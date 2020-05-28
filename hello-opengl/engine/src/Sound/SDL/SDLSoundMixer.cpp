#include "SDLSoundMixer.hpp"
#include <iostream>

namespace Engine {

SDLSoundMixer::SDLSoundMixer() {}

void SDLSoundMixer::init() {
    m_DeviceSpec.freq = 48000;
    m_DeviceSpec.format = AUDIO_S16LSB;
    m_DeviceSpec.channels = 2;
    m_DeviceSpec.samples = 1024; // must be power of 2
    m_DeviceSpec.callback = SDLSoundMixer::audioCallback;
    m_DeviceSpec.userdata = this;

    const char *defaultDeviceName = SDL_GetAudioDeviceName(0, SDL_FALSE);
    m_Device = SDL_OpenAudioDevice(defaultDeviceName, SDL_FALSE, &m_DeviceSpec,
                                   nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if (m_Device == 0) {
        std::cerr << "failed open audio device: " << SDL_GetError();
        throw std::runtime_error("audio failed");
    }

    SDL_PauseAudioDevice(m_Device, SDL_FALSE);
}

void SDLSoundMixer::add(std::string name, std::string path) {
    std::shared_ptr<SDLSoundBuffer> sound;
    sound.reset(new SDLSoundBuffer(path, m_Device, m_DeviceSpec));
    SDL_LockAudioDevice(m_Device);
    m_Sounds.push_back(sound);
    m_SoundsMap[name] = sound;
    SDL_UnlockAudioDevice(m_Device);
}

void SDLSoundMixer::play(std::string name) {
    auto sound = m_SoundsMap[name];
    sound->play(SoundBuffer::Properties::Once);
}

void SDLSoundMixer::audioCallback(void *userData, uint8_t *stream,
                                  int streamSize) {
    std::fill_n(stream, streamSize, '\0');
    auto mixer = static_cast<SDLSoundMixer *>(userData);

    for (auto sound : mixer->m_Sounds) {
        if (!sound->isPlaying()) {
            return;
        }

        uint8_t *current = &sound->data()[sound->position()];

        if (sound->rest() <= static_cast<uint32_t>(streamSize)) {
            // copy rest to buffer
            SDL_MixAudioFormat(stream, current, mixer->m_DeviceSpec.format,
                               sound->rest(), SDL_MIX_MAXVOLUME);
            sound->move(sound->rest());
        } else {
            SDL_MixAudioFormat(stream, current, mixer->m_DeviceSpec.format,
                               static_cast<uint32_t>(streamSize),
                               SDL_MIX_MAXVOLUME);
            sound->move(static_cast<uint32_t>(streamSize));
        }

        if (sound->isEnd()) {
            if (sound->isLooped()) {
                sound->reset();
            } else {
                sound->stop();
            }
        }
    }
}

} // namespace Engine