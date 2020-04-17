#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <vector>

namespace Engine {

constexpr int width = 640;
constexpr int height = 420;

#pragma pack(push, 1)
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
#pragma pack(pop)

class Canvas : public std::array<Color, width * height> {
  public:
    void save(const std::string &fileName);
    void load(const std::string &fileName);
};

struct Position {
    uint16_t x;
    uint16_t y;
};

template <size_t S> using Pixels = std::array<Position, S>;

class IRender {
  public:
    virtual void clear(Color) = 0;
    virtual void setPixel(Position, Color color) = 0;
};

} // namespace Engine
