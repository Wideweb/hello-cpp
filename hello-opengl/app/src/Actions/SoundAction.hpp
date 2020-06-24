#pragma once

#include "ActionManager.hpp"

class PlaySoundAction : public Action {
  private:
    std::string m_Sound;
    float m_Volume;
    Engine::SoundBuffer::Properties m_Properties;

  public:
    PlaySoundAction(int x, float delay, const std::string &sound, float volume,
                    Engine::SoundBuffer::Properties properties)
        : Action(x, delay), m_Sound(sound), m_Volume(volume),
          m_Properties(properties) {}

    virtual void exec() override {
        auto &sound = Engine::Application::get().getSound();
        sound.play(m_Sound, m_Volume, m_Properties);
        m_Executed = true;
    }
};

class StopSoundAction : public Action {
  private:
    std::string m_Sound;

  public:
    StopSoundAction(int x, float delay, const std::string &sound)
        : Action(x, delay), m_Sound(sound) {}

    virtual void exec() override {
        auto &sound = Engine::Application::get().getSound();
        sound.stop(m_Sound);
        m_Executed = true;
    }
};