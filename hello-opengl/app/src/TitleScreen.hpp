#pragma once

#include "App.hpp"
#include "Screen.hpp"

class TitleScreen : public Screen {
  private:
    float m_Elapsed = 0;

  public:
    TitleScreen();

    virtual void load(Context *context) override;
    virtual void update() override;
    virtual void unload(Context *context) override;
};