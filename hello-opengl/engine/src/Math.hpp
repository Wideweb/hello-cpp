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
};

struct Mat2 {
    Vec2 col1;
    Vec2 col2;

    Mat2() {}

    Mat2 operator*(const Mat2 &matrix);

    std::vector<float> data();

    static Mat2 identity();
    static Mat2 flipY();
};

struct Mat2x3 {
    Vec2 col1;
    Vec2 col2;
    Vec2 col3;

    Mat2x3() {}

    Mat2x3 operator*(const Mat2x3 &matrix);

    std::vector<float> data();

    static Mat2x3 identity();
    static Mat2x3 move(const Vec2 &vec);
    static Mat2x3 scale(float value);
    static Mat2x3 scale(float x, float y);
    static Mat2x3 rotate(float angle);
};

} // namespace Engine