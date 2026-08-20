#pragma once
#include <cmath>
#include <cassert> 

struct Vec3 {
    float x, y, z;
    constexpr Vec3() : x(0), y(0), z(0) {}
    constexpr Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

inline Vec3 operator-(const Vec3& a) {
    return Vec3(-a.x, -a.y, -a.z);
}

inline Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Scalar multiplication
inline Vec3 operator*(const Vec3& a, float s) {
    return Vec3(a.x * s, a.y * s, a.z * s);
}

// Dot product
inline float dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product
inline Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

// Euclidean distance
inline float length(const Vec3& a) {
    return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// Unit vector
inline Vec3 normalise(const Vec3& a) {
    float len = length(a);
    assert(len > 1e-6f);
    return a * (1.0f / len);
}