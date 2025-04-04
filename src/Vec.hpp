#ifndef VEC_HPP
#define VEC_HPP

#include <algorithm>
#include <cmath>
#include <cstdio>

constexpr float almostZero = 0.00001f;

typedef struct Vec2 {
  float x, y;

  Vec2() {
    y = 0.0f;
    x = 0.0f;
  }

  Vec2(float _x, float _y) {
    x = _x;
    y = _y;
  }

  inline Vec2 add(struct Vec2 s) const { return {x + s.x, y + s.y}; }

  inline Vec2 sub(struct Vec2 s) const { return {x - s.x, y - s.y}; }

  float dot(struct Vec2 s) const { return x * s.x + y * s.y; }

  Vec2 div(float s) const { return {x / s, y / s}; }

  Vec2 projection(struct Vec2 s) const {
    float dotProduct = x * s.x + y * s.y;
    float magSquared = s.x * s.x + s.y * s.y;
    if (magSquared == 0) {
      return Vec2();
    }
    auto scale = dotProduct / magSquared;
    return s.multiply(scale);
  }

  Vec2 multiply(float scalar) const { return {x * scalar, y * scalar}; }

  Vec2 setmag(float scalar) const {
    float mag = sqrt(x * x + y * y);
    if (mag == 0.0f) {
      mag = almostZero;
    }
    return {x * scalar / mag, y * scalar / mag};
  }

  float mag() const { return sqrt(x * x + y * y); }

  float distance(Vec2 o) const {
    float dx = o.x - x;
    float dy = o.y - y;
    return sqrt(dx * dx + dy * dy);
  }

  inline bool isNan() { return x != x || y != y; }
} Vec2;

typedef struct Vec3 {
  float x, y, z;

  Vec3(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
  }

  Vec3() { x = y = z = 0.0f; }
} Vec3;

typedef struct Square {
  Vec2 low, high;

  Square() { low = high = {0, 0}; }
  Square(Vec2 _low, Vec2 _high) {
    low = _low;
    high = _high;
  }

  inline bool Contains(Vec2 p) const {
    return (p.x >= low.x && p.x <= high.x) && (p.y >= low.y && p.y <= high.y);
  }

  bool Intersects(Square &r) const {
    return std::max(r.low.x, low.x) < std::min(r.high.x, high.x) &&
           std::max(r.low.y, low.y) < std::min(r.high.y, high.y);
  }
} Square;

bool testSquare();

#endif
