#include "vec3.h"
#include "mat4.h"
#include "vec4.h"
#include "debug.h"
#include "pipeline.h"
#include "raster.h"
#include "ppm.h"
#include "obj_loader.h"
#include <optional>
#include <iostream> 

int main() {

    auto m = load_obj(std::string(PROJECT_ROOT) + "/assets/cube.obj");
    if (!m) {
        std::cerr << "Failed to load cube.obj\n";
        return 1;
    }

    Vec3 eye(2, 5, 7);
    Vec3 up_hint(0, 1, 0);
    Vec3 target(0, 0, 0);

    const int width  = 800;
    const int height = 600;

    float fovy    = 60.0f * 3.14159265f / 180.0f;  // 60 degrees, in radians
    float aspect  = static_cast<float>(width) / height;
    float near_pl = 0.1f;
    float far_pl  = 100.0f;

    FrameBuffer fb(width, height);
    clear(fb);

    Mat4 M = Mat4::identity();
    Mat4 V = Mat4::look_at(eye, target, up_hint);
    Mat4 P = Mat4::perspective(fovy, aspect, near_pl, far_pl);

    Mat4 MVP = P * V * M;

    size_t vertex_count = m->positions.size();
    size_t index_count = m->indices.size();
 
    std::vector<ScreenPoint> points(vertex_count);
    for (int i = 0; i < vertex_count; i++) {
        points[i] = project_vertex(MVP, m->positions[i], width, height);
    }

    for (int i = 0; i < index_count; i+=3) {
        ScreenPoint a = points[m->indices[i + 0]];
        ScreenPoint b = points[m->indices[i + 1]];
        ScreenPoint c = points[m->indices[i + 2]];
        
        draw_line(fb, a, b, {255, 255, 255});
        draw_line(fb, b, c, {255, 255, 255});
        draw_line(fb, c, a, {255, 255, 255});
    }

    write_ppm(fb, "E:/dev/engine/output.ppm");
}
