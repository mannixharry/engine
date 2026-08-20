#pragma once

#include <vector>
#include <cstdint>
#include <cassert>

struct Colour {
    uint8_t r, g, b;
};

static_assert(sizeof(Colour) == 3, "Colour struct must not be padded");
// SDL_UpdateTexture takes void* (and assumes 3 bytes).
// Compiler padding Colour would break this contract.

struct FrameBuffer {
    int width, height;
    std::vector<uint8_t> pixels;

    FrameBuffer(int width, int height)
        : width(width), height(height), pixels(static_cast<size_t>(width) * height * 3) {}
};

inline void set_pixel(FrameBuffer& fb, int x, int y, Colour c) {
    if (x < 0 || x >= fb.width || y < 0 || y >= fb.height) {
        return; // Future: raise error here to validate prior clipping
    }
    size_t idx = 3 * (static_cast<size_t>(y) * fb.width + x);
    fb.pixels[idx + 0] = c.r;
    fb.pixels[idx + 1] = c.g;
    fb.pixels[idx + 2] = c.b;
}

inline void clear(FrameBuffer& fb, Colour c = {0, 0, 0}) {
    for (size_t i=0; i < fb.pixels.size(); i+=3) {
        fb.pixels[i + 0] = c.r;
        fb.pixels[i + 1] = c.g;
        fb.pixels[i + 2] = c.b;
    }
}