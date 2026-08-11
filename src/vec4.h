#pragma once
#include <cmath>

struct Vec4 {
    float x, y, z, w;
    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vec4(Vec3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {} // From Vec3

    Vec3 xyz() const {
        return Vec3(x, y, z);
    }
};