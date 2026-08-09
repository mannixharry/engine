#pragma once 

#include <cstdio>
#include "mat4.h"
#include "vec4.h"

inline void print(const Mat4& a) {
    for (int i = 0; i < 4; i++) {
        std::printf("[ %8.4f %8.4f %8.4f %8.4f ]\n",
                    a.m[i][0], a.m[i][1], a.m[i][2], a.m[i][3]);
    }
    std::printf("\n");
}

inline void print(const Vec4& v) {
    std::printf("( %8.4f %8.4f %8.4f %8.4f )\n", v.x, v.y, v.z, v.w);
}