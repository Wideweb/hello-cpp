#include "Math.hpp"
#include <cmath>

namespace Engine {

Vec2::Vec2() {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2 &vec) { return Vec2(x + vec.x, y + vec.y); }

Vec2 Vec2::operator-(const Vec2 &vec) { return Vec2(x - vec.x, y - vec.y); }

Vec2 Vec2::operator/(float value) { return Vec2(x / value, y / value); }

Vec2 Vec2::operator*(float value) { return Vec2(x * value, y * value); }

float Vec2::magnitude() { return std::sqrt(x * x + y * y); }

Vec2 Vec2::unit() { return Vec2(x, y) / magnitude(); }

Vec2 Vec2::normalL() { return Vec2(-x, y); }

float Vec2::dot(const Vec2 &vec) { return x * vec.x + y * vec.y; }

Mat2 Mat2::identity() {
    Mat2 matrix;
    matrix.col1.x = 1;
    matrix.col2.y = 1;
    return matrix;
}

Mat2 Mat2::flipY() {
    auto matrix = Mat2::identity();
    matrix.col1.x = -1;
    return matrix;
}

std::vector<float> Mat2::data() {
    return {col1.x, col2.x,

            col1.y, col2.y};
}

Mat2x3 Mat2x3::operator*(const Mat2x3 &matrix) {
    Mat2x3 result;

    result.col1.x = col1.x * matrix.col1.x + col2.x * matrix.col1.y;
    result.col1.y = col1.y * matrix.col1.x + col2.y * matrix.col1.y;

    result.col2.x = col1.x * matrix.col2.x + col2.x * matrix.col2.y;
    result.col2.y = col1.y * matrix.col2.x + col2.y * matrix.col2.y;

    result.col3.x = col1.x * matrix.col3.x + col2.x * matrix.col3.y + col3.x;
    result.col3.y = col1.y * matrix.col3.x + col2.y * matrix.col3.y + col3.y;

    return result;
}

std::vector<float> Mat2x3::data() {
    return {col1.x, col2.x, col3.x,

            col1.y, col2.y, col3.y};
}

Mat2x3 Mat2x3::identity() {
    Mat2x3 matrix;
    matrix.col1.x = 1;
    matrix.col2.y = 1;
    return matrix;
}

Mat2x3 Mat2x3::move(const Vec2 &vec) {
    auto matrix = Mat2x3::identity();
    matrix.col3 = vec;
    return matrix;
}

Mat2x3 Mat2x3::scale(float value) {
    auto matrix = Mat2x3::identity();
    matrix.col1.x = value;
    matrix.col2.y = value;
    return matrix;
}

Mat2x3 Mat2x3::scale(float x, float y) {
    auto matrix = Mat2x3::identity();
    matrix.col1.x = x;
    matrix.col2.y = y;
    return matrix;
}

Mat2x3 Mat2x3::rotate(float angle) {
    auto matrix = Mat2x3::identity();

    matrix.col1.x = std::cos(angle);
    matrix.col1.y = std::sin(angle);

    matrix.col2.x = -std::sin(angle);
    matrix.col2.y = std::cos(angle);

    return matrix;
}

} // namespace Engine