#pragma once

#include <sstream>
#include <vector>

namespace Engine {

struct Mat2x3;

struct Vec2 {
    float x = 0;
    float y = 0;

    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2 &vec);
    Vec2 operator-(const Vec2 &vec);
    Vec2 operator/(float value);
    Vec2 operator*(float value);

    float magnitude();
    float inverseMagnitude();
    Vec2 unit();
    Vec2 normalL();
    float dot(const Vec2 &vec);

    friend std::ostringstream &operator<<(std::ostringstream &out,
                                          const Vec2 &v) {
        out << v.x << " ";
        out << v.y;
        return out;
    }
};

struct Vec3 {
    float x = 0;
    float y = 0;
    float z = 0;

    Vec3();
    Vec3(float x, float y, float z);

    friend std::ostringstream &operator<<(std::ostringstream &out,
                                          const Vec3 &v) {
        out << v.x << " ";
        out << v.y << " ";
        out << v.z;
        return out;
    }
};

struct Mat2x3 {
    Vec2 col1;
    Vec2 col2;
    Vec2 col3;

    Mat2x3() {}

    Mat2x3 operator*(const Mat2x3 &matrix);

    std::vector<float> data();

    static Mat2x3 identity();
    static Mat2x3 flipY();
    static Mat2x3 move(const Vec2 &vec);
    static Mat2x3 scale(float value);
    static Mat2x3 scale(float x, float y);
    static Mat2x3 rotate(float angle);
};

struct Rect {
    float x;
    float y;
    float w;
    float h;

    Rect() {}
    Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

    friend std::ostringstream &operator<<(std::ostringstream &out,
                                          const Rect &r) {
        out << r.x << " ";
        out << r.y << " ";
        out << r.w << " ";
        out << r.h;
        return out;
    }
};

} // namespace Engine