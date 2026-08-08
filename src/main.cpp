#include <fstream>
#include <iostream>

int main() {
    const int width = 256; 
    const int height = 256; 

    std::ofstream out("output.ppm");
    out << "P3\n" << width << ' ' << height << "\n255\n";
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = float(x) / (width - 1);
            float g = float(y) / (height - 1);
            float b = 0.25f;

            int ir = int(255.99f * r);
            int ig = int(255.999f * g);
            int ib = int(255.999f * b);
            
            out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std:: cout << "Wrote output.ppm\n";
    return 0;
}