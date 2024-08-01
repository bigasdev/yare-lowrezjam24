#ifndef __COMMON_HPP__
#define __COMMON_HPP__
#pragma once
#include "random.hpp"
#include <iostream>
// enums
enum State { IDLE, UPDATE, UNAVALIABLE };

enum Tag { HERO, ENEMY, GROUND, WALL, BULLET, ITEM, NONE };
enum ProjectileTag { PROJECTILE_HERO, PROJECTILE_ENEMY, PROJECTILE_ENVIRONMENT, PROJECTILE_NONE };

using Random = effolkronium::random_static;

// important stuff to entities
struct vec2f {
  float x, y;
  vec2f() : x(0.0f), y(0.0f) {}

  vec2f(float p_x, float p_y) : x(p_x), y(p_y) {}

  void print() { std::cout << x << ", " << y << std::endl; }
  bool zero() { return x == 0 && y == 0; }
  int distance(vec2f p){
    return std::sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
  }
  bool operator==(const vec2f &other) const {
    return (x == other.x) && (y == other.y);
  }
  vec2f operator+(const vec2f &other) const {
    return vec2f(x + other.x, y + other.y);
  }
  vec2f operator+=(const vec2f &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  bool operator!=(const vec2f &other) const { return !(*this == other); }
  vec2f operator*(double scalar) const { return vec2f(x * scalar, y * scalar); }
  vec2f operator*=(double scalar) const {
    return vec2f(x * scalar, y * scalar);
  }

  double magnitude() const { return std::sqrt(x * x + y * y); }
  vec2f normalize() const {
    double mag = magnitude();
    if (mag == 0)
      return vec2f(0, 0);
    return vec2f(x / mag, y / mag);
  }
  vec2f operator/(double scalar) const { return vec2f(x / scalar, y / scalar); }

  vec2f operator-(const vec2f &other) const {
    return vec2f(x - other.x, y - other.y);
  }
};
struct vec2i {
  int x, y;
  vec2i() : x(0), y(0) {}
  vec2i(int p_x, int p_y) : x(p_x), y(p_y) {}
  void print() { std::cout << x << ", " << y << std::endl; }
  bool zero() { return x == 0 && y == 0; }
  bool operator==(const vec2i &other) const {
    return (x == other.x) && (y == other.y);
  }
  vec2i operator+(const vec2i &other) const {
    return vec2i(x + other.x, y + other.y);
  }
  vec2i operator+=(const vec2i &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  bool operator!=(const vec2i &other) const { return !(*this == other); }
  vec2i operator*(int scalar) const { return vec2i(x * scalar, y * scalar); }
  vec2i operator*=(int scalar) const {
    return vec2i(x * scalar, y * scalar);
  }

  int magnitude() const { return std::sqrt(x * x + y * y); }
  vec2i normalize() const {
    int mag = magnitude();
    if (mag == 0)
      return vec2i(0, 0);
    return vec2i(x / mag, y / mag);
  }
  vec2i operator/(int scalar) const { return vec2i(x / scalar, y / scalar); }

  vec2i operator-(const vec2i &other) const {
    return vec2i(x - other.x, y - other.y);
  }
};
struct vec3f {
  float x, y, z;
  vec3f() : x(0.0f), y(0.0f), z(0.0f) {}
  vec3f(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z) {}
  void print() { std::cout << x << ", " << y << ", " << z << std::endl; }
};
/// <summary>
/// Structure that will have position and radius
/// </summary>
struct Area {
  float x, y, w, h;
  Area() : x(0), y(0), w(50), h(50) {}
  Area(float pX, float pY, float pW, float pH) : x(pX), y(pY), w(pW), h(pH) {}

  bool intersects(const Area pArea) {
    return (x < pArea.x + pArea.w) && (pArea.x < x + w) &&
           (y < pArea.y + pArea.h) && (pArea.y < y + h);
  }
};

struct CollisionBox2D {
  vec2f offset;
  vec2f scale;
  CollisionBox2D() : offset(0, 0), scale(0, 0) {}
  CollisionBox2D(vec2f _offset, vec2f _scale)
      : offset(_offset), scale(_scale) {}
};

struct Stat {
  float value;
  float max;
  Stat() : value(0), max(0) {}
  Stat(float _value, float _max) : value(_value), max(_max) {}

  void add(float _value) {
    value += _value;
    if (value > max) {
      value = max;
    }
  }
};

struct IntStat {
  int value;
  int max;
  IntStat() : value(0), max(0) {}
  IntStat(int _value, int _max) : value(_value), max(_max) {}

  void add(int _value) {
    value += _value;
    if (value > max) {
      value = max;
    }
  }

  void randomize(int min, int val) { value = Random::get(min, val); }
};

struct Life : public Stat {
  Life() : Stat() {}
  Life(float _value, float _max) : Stat(_value, _max) {}

  bool is_alive() { return value > 0; }
};

inline float rnd(float min, float max) { return Random::get(min, max); }

inline int rnd(int min, int max) { return Random::get(min, max); }

#endif
