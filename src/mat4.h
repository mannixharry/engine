#pragma once
#include <cmath>
#include "vec3.h"
#include "vec4.h"

// Right-handed. Camera at origin looking down -z, with +y up, and +x right.
// Vec3 and Vec 4 are column vectors.
// NDC (Normalised Device Coordinates) chosen as [-1, 1]^3

struct Mat4 {
    float m[4][4];

    static Mat4 zero() {
        return Mat4{}; // Zero initialises
    }

    static Mat4 identity() {
        return Mat4{{{1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, 0, 1}}};
    }

    static Mat4 translation(const Vec3& t) {
        Mat4 r = Mat4::identity();
        r.m[0][3] = t.x;
        r.m[1][3] = t.y;
        r.m[2][3] = t.z;
        return r;
    }

    static Mat4 scale(const Vec3& s) {
        Mat4 r = Mat4::identity();
        r.m[0][0] = s.x;
        r.m[1][1] = s.y;
        r.m[2][2] = s.z;
        return r;
    }

    static Mat4 rotation_x(float radians) {
        Mat4 r = Mat4::identity();
        r.m[1][1] = std::cos(radians);
        r.m[1][2] = -std::sin(radians);
        r.m[2][1] = std::sin(radians);
        r.m[2][2] = std::cos(radians);
        return r;
    }

    static Mat4 rotation_y(float radians) {
        Mat4 r = Mat4::identity();
        r.m[0][0] = std::cos(radians);
        r.m[0][2] = std::sin(radians);
        r.m[2][0] = -std::sin(radians);
        r.m[2][2] = std::cos(radians);
        return r;
    }

    static Mat4 rotation_z(float radians) {
        Mat4 r = Mat4::identity();
        r.m[0][0] = std::cos(radians);
        r.m[0][1] = -std::sin(radians);
        r.m[1][0] = std::sin(radians);
        r.m[1][1] = std::cos(radians);
        return r;
    }

    static Mat4 look_at(const Vec3& eye, const Vec3& target, const Vec3& up_hint) {
        // Orthonormal basis of camera space
        // Future: fix issues arising when f and up_hint are (nearly) parallel
        Vec3 f = normalise(target - eye);
        Vec3 r = normalise(cross(f, up_hint));
        Vec3 u = cross(r, f);

        Mat4 v = Mat4::identity();

        v.m[0][0] =  r.x;  v.m[0][1] =  r.y;  v.m[0][2] =  r.z;  v.m[0][3] = -dot(r, eye);
        v.m[1][0] =  u.x;  v.m[1][1] =  u.y;  v.m[1][2] =  u.z;  v.m[1][3] = -dot(u, eye);
        v.m[2][0] = -f.x;  v.m[2][1] = -f.y;  v.m[2][2] = -f.z;  v.m[2][3] =  dot(f, eye);
        // Bottom row (0, 0, 0, 1)

        return v;
    }

    static Mat4 perspective(float fovy_radians, float aspect, float near_plane, float far_plane) {
        Mat4 p = Mat4::zero();
        float t = std::tan(fovy_radians / 2.0f);

        p.m[0][0] = 1.0f / (t * aspect);
        p.m[1][1] = 1.0f / t;

        p.m[2][2] = -(far_plane + near_plane) / (far_plane - near_plane);
        p.m[2][3] = -(2.0f * far_plane * near_plane) / (far_plane - near_plane);

        p.m[3][2] = -1.0f;

        return p;
    }
};

// Future: unroll to optimize
inline Mat4 operator*(const Mat4& a, const Mat4& b) {
    Mat4 c = Mat4::zero();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
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
