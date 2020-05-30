#pragma once

#include "MenuItem.hpp"

#include <vector>

class Menu {
  private:
    std::vector<MenuItem> m_Items;

  public:
    Menu(const std::vector<MenuItem> &items);

    void load(Context *);
    void update();
    void unload(Context *);

  private:
    void onItemSelected(const MenuItem &item);
};