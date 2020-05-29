#pragma once

#include "Screen.hpp"
#include <map>
#include <memory>
#include <string>

class ScreenManager {
  private:
    std::shared_ptr<Screen> m_Current;
    std::map<std::string, std::shared_ptr<Screen>> m_ScreenMap;
    Context *m_Context;
    static ScreenManager *s_Instance;

  public:
    ScreenManager();
    ~ScreenManager();

    void init(Context *context);
    void update();
    void add(std::string screenId, Screen *screen);
    void goTo(std::string screenId);
    void unload();

    static ScreenManager &get() { return *s_Instance; }
};