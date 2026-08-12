#include "vec3.h"
#include "mat4.h"
#include "vec4.h"
#include "debug.h"
#include "pipeline.h"
#include "raster.h"
#include "ppm.h"

int main() {

    const Vec3 cube_vertices[8] = {
        {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},   // back face  (z = -1)
        {-1, -1,  1}, {1, -1,  1}, {1, 1,  1}, {-1, 1,  1},   // front face (z = +1)
    };

    const int cube_edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},   // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4},   // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7},   // connecting
    };

    Vec3 eye(2, 3, 4);
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

    ScreenPoint points[8];
    for (int i = 0; i < 8; i++) {
        points[i] = project_vertex(MVP, cube_vertices[i], width, height);
    }

    for (const auto& edge : cube_edges) {
        ScreenPoint a = points[edge[0]];
        ScreenPoint b = points[edge[1]];

        draw_line(fb, a, b, {255, 255, 255});
    }

    write_ppm(fb, "E:/dev/engine/output.ppm");
}
