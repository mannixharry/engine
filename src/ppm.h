#pragma once
#include "framebuffer.h"
#include <fstream> 
#include <string> 

inline void write_ppm(const FrameBuffer& fb, std::string path) {
    std::ofstream out(path, std::ios::binary);
    out << "P6\n" << fb.width << " " << fb.height << "\n255\n";
    out.write(reinterpret_cast<const char*>(fb.pixels.data()), fb.pixels.size());
}