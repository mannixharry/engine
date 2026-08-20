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
#include <cmath>

int main() {

    const int width  = 800;
    const int height = 600;

    Window window("engine", width, height);
    if (!window.ok()) {
        return 1;
    }
    window.set_mouse_capture(true); // hides cursor, gives unbounded deltas

    auto m = load_obj(std::string(PROJECT_ROOT) + "/assets/cube.obj");
    if (!m) {
        std::cerr << "Failed to load cube.obj\n";
        return 1;
    }

    Camera cam({0.0f, 0.0f, 10.0f});
    FrameBuffer fb(width, height);

    Uint64 last_ns = SDL_GetTicksNS();

    bool running = true; 
    float angle_x = 0.0f;

    while (running) {
        const Uint64 now_ns = SDL_GetTicksNS();
        const float dt = std::min(static_cast<float>((now_ns - last_ns) * 1e-9f), 0.05f);
        // Avoids time accumulation when debugging code
    
        last_ns = now_ns; 

        float mouse_dx = 0.0f;
        float mouse_dy = 0.0f; 

        SDL_Event e; 
        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_EVENT_QUIT) { running = false; }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) { running = false; }
            if (e.type == SDL_EVENT_MOUSE_MOTION) {
                mouse_dx += e.motion.xrel;
                mouse_dy += e.motion.yrel; 
            }
        }

        constexpr float kSensitivity = 0.0025f; // radians per pixel
        cam.rotate(-kSensitivity * mouse_dx, -kSensitivity * mouse_dy);

        Vec3 dir{0.0f, 0.0f, 0.0f};
        const bool* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W])     { dir.z += 1.0f; }
        if (keys[SDL_SCANCODE_S])     { dir.z -= 1.0f; }
        if (keys[SDL_SCANCODE_D])     { dir.x += 1.0f; }
        if (keys[SDL_SCANCODE_A])     { dir.x -= 1.0f; }
        if (keys[SDL_SCANCODE_SPACE]) { dir.y += 1.0f; }
        if (keys[SDL_SCANCODE_LCTRL]) { dir.y -= 1.0f; }

        if(length(dir) > 0.0f) {
            constexpr float kSpeed = 5.0f; // World units per second
            cam.move(normalise(dir) * (kSpeed * dt)); 
        }

        const float aspect  = static_cast<float>(width) / height;

        Mat4 M = Mat4::rotation_x(angle_x);
        //constexpr float kSpin = kTwoPi / 8.0f;   // one revolution per 8 seconds
        //angle_x = std::remainder(angle_x + kSpin * dt, kTwoPi);

        Mat4 V = cam.view();
        Mat4 P = cam.projection(aspect);

        Mat4 MVP = P * V * M;

        size_t vertex_count = m->positions.size();
        size_t index_count = m->indices.size();
        
        std::vector<ScreenPoint> points(vertex_count);
        for (int i = 0; i < vertex_count; i++) {
            points[i] = project_vertex(MVP, m->positions[i], width, height);
        }

        clear(fb, Colour{0,0,0});

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