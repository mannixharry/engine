#include "vec3.h"
#include "mat4.h"
#include "vec4.h"
#include "debug.h"
#include "pipeline.h"
#include "raster.h"
#include "ppm.h"
#include "obj_loader.h"
#include "window.h"
#include "constants.h"
#include "camera.h"
#include <optional>
#include <iostream> 


int main() {

    const int width  = 800;
    const int height = 600;
    float aspect  = static_cast<float>(width) / height;

    Window window("engine", width, height);
    if (!window.ok()) {
        return 1;
    }

    auto m = load_obj(std::string(PROJECT_ROOT) + "/assets/cube.obj");
    if (!m) {
        std::cerr << "Failed to load cube.obj\n";
        return 1;
    }

    Camera c({0.0f, 0.0f, 10.0f});
    FrameBuffer fb(width, height);

    bool running = true; 
    float angle_x = 0;

    while (running) {
        SDL_Event e; 
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
                running = false;
            }
        }

        Mat4 M = Mat4::rotation_x(angle_x);
        angle_x += kTwoPi / 1000.0f;
        angle_x = std::remainder(angle_x, kTwoPi);

        Mat4 V = c.view();
        Mat4 P = c.projection(aspect);

        Mat4 MVP = P * V * M;

        size_t vertex_count = m->positions.size();
        size_t index_count = m->indices.size();
        
        std::vector<ScreenPoint> points(vertex_count);
        for (int i = 0; i < vertex_count; i++) {
            points[i] = project_vertex(MVP, m->positions[i], width, height);
        }

        clear(fb);

        for (int i = 0; i < index_count; i+=3) {
            ScreenPoint a = points[m->indices[i + 0]];
            ScreenPoint b = points[m->indices[i + 1]];
            ScreenPoint c = points[m->indices[i + 2]];
            
            draw_line(fb, a, b, {255, 255, 255});
            draw_line(fb, b, c, {255, 255, 255});
            draw_line(fb, c, a, {255, 255, 255});
        }

        window.present(fb);
    }
    //write_ppm(fb, "E:/dev/engine/output.ppm");
}