#pragma once 
#include "vec3.h"
#include <vector> 
#include <fstream> 
#include <sstream> 

#include <optional> 
#include <string> 

struct Mesh {
    std::vector<Vec3> positions;  
    std::vector<int> indices;
};

// Very basic .obj loader (to load cube.obj)
inline std::optional<Mesh> load_obj(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        return std::nullopt;
    }
    Mesh m; 
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword; 
        iss >> keyword; 
        if (keyword == "v") {
            float x, y, z; 
            iss >> x >> y >> z;
            Vec3 pos(x, y, z);
            m.positions.push_back(pos);
        } else if (keyword == "f") {
            int a, b, c;
            iss >> a >> b >> c; 
            m.indices.push_back(a - 1);
            m.indices.push_back(b - 1);
            m.indices.push_back(c - 1);
        }
    }
    return m;
}