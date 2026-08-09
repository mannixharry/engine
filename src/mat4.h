#pragma once
#include <cmath>
#include "vec3.h"
#include "vec4.h"

struct Mat4 {
    float m[4][4];

    Mat4()
        : m {{1, 0, 0, 0},
             {0, 1, 0, 0},
             {0, 0, 1, 0},
             {0, 0, 0, 1}} {}

    static Mat4 translation(const Vec3& t) {
        Mat4 r; // Identity
        r.m[0][3] = t.x;
        r.m[1][3] = t.y;
        r.m[2][3] = t.z;
        return r; 
    }

    static Mat4 scale(const Vec3& s) {
        Mat4 r; 
        r.m[0][0] = s.x;
        r.m[1][1] = s.y;
        r.m[2][2] = s.z;
        return r;
    }

    static Mat4 rotation_x(float radians) {
        Mat4 r; 
        r.m[1][1] = std::cos(radians);
        r.m[1][2] = -std::sin(radians);
        r.m[2][1] = std::sin(radians);
        r.m[2][2] = std::cos(radians);
        return r;
    }

    static Mat4 rotation_y(float radians) {
        Mat4 r; 
        r.m[0][0] = std::cos(radians);
        r.m[0][2] = std::sin(radians);
        r.m[2][0] = -std::sin(radians);
        r.m[2][2] = std::cos(radians);
        return r;
    }

    static Mat4 rotation_z(float radians) {
        Mat4 r; 
        r.m[0][0] = std::cos(radians);
        r.m[0][1] = -std::sin(radians);
        r.m[1][0] = std::sin(radians);
        r.m[1][1] = std::cos(radians);
        return r;
    }
};

inline Mat4 operator*(const Mat4& a, const Mat4& b) {
    Mat4 c;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            float sum = 0.0f;
            for (int k=0; k<4; k++) {
                sum += a.m[i][k] * b.m[k][j];
            }
            c.m[i][j] = sum;
        }
    }
    return c;
}

inline Vec4 operator*(const Mat4& a, const Vec4& v) {
    Vec4 r;
    r.x = a.m[0][0] * v.x + a.m[0][1] * v.y + a.m[0][2] * v.z + a.m[0][3] * v.w;
    r.y = a.m[1][0] * v.x + a.m[1][1] * v.y + a.m[1][2] * v.z + a.m[1][3] * v.w;
    r.z = a.m[2][0] * v.x + a.m[2][1] * v.y + a.m[2][2] * v.z + a.m[2][3] * v.w;
    r.w = a.m[3][0] * v.x + a.m[3][1] * v.y + a.m[3][2] * v.z + a.m[3][3] * v.w;
    return r; 
}
