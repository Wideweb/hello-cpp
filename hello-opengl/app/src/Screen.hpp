#pragma once

#include "App.hpp"

class Screen {
  public:
    virtual ~Screen() = default;

    virtual void load(Context *) = 0;
    virtual void update() = 0;
    virtual void unload(Context *) = 0;
};