#pragma once

#include "Application.hpp"

extern Engine::Application *Engine::createApplication();

void main() {
    auto app = Engine::createApplication();
    app->run();
    delete app;
}