#pragma once

#include "framebuffer.h"
#include "pipeline.h"
#include <cmath>

// DDA (Digital Differential Analizer line drawer)
inline void draw_line(FrameBuffer& fb, const ScreenPoint& a, const ScreenPoint& b, Colour c) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    int steps = static_cast<int>(std::max(std::fabs(dx), std::fabs(dy)));

    if (steps == 0) {
        set_pixel(fb, std::lround(a.x), std::lround(a.y), c);
        return; // Edge case for single points
    }

    float x_inc = dx / steps;
    float y_inc = dy / steps;

    for (int i = 0; i <= steps; i++) {
        set_pixel(fb, std::lround(a.x + i * x_inc), std::lround(a.y + i * y_inc), c);
    }
}