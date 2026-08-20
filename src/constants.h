#pragma once
#include "vec3.h"

constexpr float kPi = 3.14159265358979323846f;
constexpr float  kTwoPi  = 2.0f * kPi;

inline constexpr float radians(float degrees) {
    return degrees * (kPi / 180.0f);
}

inline constexpr Vec3 kWorldUp{0.0f, 1.0f, 0.0f};


