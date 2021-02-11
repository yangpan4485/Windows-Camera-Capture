#include "video_render_sdl.h"

#include <iostream>
#include "libyuv.h"

SDLRender::SDLRender() {
    Init();
}

SDLRender::~SDLRender() {
    Destroy();
}

void SDLRender::SetWindow(void* handle) {
    hwnd_ = (HWND)handle;
    window_ = SDL_CreateWindowFrom(handle);
    if (window_ == nullptr) {
        std::cout << SDL_GetError() << std::endl;
    }
}

void SDLRender::Render(uint8_t* data, uint32_t width, uint32_t height) {
    if (width != width_ || height != height_) {
        width_ = width;
        height_ = height;
        InitRender();
        InitTexture();
    }
    SDL_UpdateTexture(texture_, NULL, data, width_);

    RECT rect;
    GetClientRect(hwnd_, &rect);
    SDL_Rect sdl_rect;
    sdl_rect.x = rect.left;
    sdl_rect.y = rect.top;
    sdl_rect.w = rect.right - rect.left;
    sdl_rect.h = rect.bottom - rect.top;
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, texture_, NULL, &sdl_rect);
    SDL_RenderPresent(renderer_);
}

void SDLRender::Init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
        std::cout << "SDL2 init failed" << std::endl;
        return;
    }
}
void SDLRender::Destroy() {
    if (window_) {
        SDL_DestroyWindow(window_);
    }
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
    }
    if (texture_) {
        SDL_DestroyTexture(texture_);
    }
    SDL_Quit();
}
void SDLRender::InitRender() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
    }
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}

void SDLRender::InitTexture() {
    if (texture_) {
        SDL_DestroyTexture(texture_);
    }
    texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, width_, height_);
}

