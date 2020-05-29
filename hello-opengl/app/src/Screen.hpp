#pragma once

#include "Application.hpp"

typedef Engine::Layer Context;

class Screen {
  public:
    virtual ~Screen() = default;

    virtual void load(Context *) = 0;
    virtual void update() = 0;
    virtual void unload(Context *) = 0;
};