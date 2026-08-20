#pragma once

constexpr float kPi = 3.14159265358979323846f;
constexpr float  kTwoPi  = 2.0f * kPi;

constexpr float radians(float degrees) {
    return degrees * (kPi / 180.0f);
}