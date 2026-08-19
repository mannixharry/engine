#pragma once
#include <vector>
#include "vec3.h"

struct Mesh {
    std::vector<Vec3> positions;  
    std::vector<int> indices;
};
