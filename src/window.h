#pragma once
#include <SDL3/SDL.h> 
#include <cassert>
#include "framebuffer.h"

class Window {
    public:
        Window(const char* title, int width, int height) {

            width_ = width; 
            height_ = height; 

            if (!SDL_Init(SDL_INIT_VIDEO)) {
                SDL_Log("SDL_Init: %s", SDL_GetError());
                return;
            }

            if (!SDL_CreateWindowAndRenderer(title, width, height, 0, &window_, &renderer_)) {
                SDL_Log("SDL_CreateWindowAndRenderer: %s", SDL_GetError());
                return;
            }

            texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, width, height);
            if (!texture_) {
                SDL_Log("SDL_CreateTexture: %s", SDL_GetError());
                return; 
            }

            SDL_SetRenderVSync(renderer_, 1);
        }

        ~Window() {
            SDL_DestroyTexture(texture_);
            SDL_DestroyRenderer(renderer_);
            SDL_DestroyWindow(window_);
            SDL_Quit();
        }

        // Remove copy operations
        Window(const Window&)            = delete;
        Window& operator=(const Window&) = delete;

        bool ok() const {
            return texture_ != nullptr;
        }

        void present(const FrameBuffer& fb) {

            assert(fb.width == width_ && fb.height == height_);

            // 3 bytes per pixel (RGB24), width_ pixels per row
            SDL_UpdateTexture(texture_, nullptr, fb.pixels.data(), 3 * width_);
            SDL_RenderClear(renderer_);
            SDL_RenderTexture(renderer_, texture_, nullptr, nullptr);
            SDL_RenderPresent(renderer_);
        }

        void set_mouse_capture(bool capture) {
            SDL_SetWindowRelativeMouseMode(window_, capture);
        }

    private:

        SDL_Window* window_     = nullptr;
        SDL_Renderer* renderer_ = nullptr; 
        SDL_Texture* texture_   = nullptr;

        int width_  = 0;
        int height_ = 0;
};