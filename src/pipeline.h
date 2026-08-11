#pragma once
#include "vec3.h"
#include "mat4.h"
#include "vec4.h"
#include <cassert>

struct ScreenPoint {
    float x, y;     // pixel coordinates, origin top-left
    float z;        // NDC depth [-1, 1], for z-buffering
    float inv_w;    // 1/w, for later perspective-correct interpolation
};

inline ScreenPoint clip_to_screen(const Vec4& clip, int width, int height) {
    assert(clip.w > 0.0f && "vertex at or behind the camera; near-plane clipping not yet implemented");
    float inv_w = 1.0f / clip.w;
    Vec3 ndc = clip.xyz() * inv_w;

    ScreenPoint p; 
    p.x = 0.5f * width * (1 + ndc.x);
    p.y = 0.5f * height * (1 - ndc.y); // Flip vertically (screen +y runs top-to-bottom)
    p.z = ndc.z; 
    p.inv_w = inv_w; 

    return p;
}

inline ScreenPoint project_vertex(const Mat4& mvp, const Vec3& p, int width, int height) {
    Vec4 clip = mvp * Vec4(p, 1.0f);
    return clip_to_screen(clip, width, height);
}