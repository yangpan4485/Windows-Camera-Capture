#pragma once
#include <Windows.h>
extern "C" {
#include "SDL.h"
}

class SDLRender {
public:
    SDLRender();
    ~SDLRender();

    void SetWindow(void* handle);
    void Render(uint8_t* data, uint32_t width, uint32_t height);

private:
    void Init();
    void Destroy();
    void InitRender();
    void InitTexture();

private:
    uint32_t width_{};
    uint32_t height_{};

    SDL_Window* window_{}; // ´°¿Ú
    SDL_Renderer* renderer_{}; // äÖÈ¾Æ÷
    SDL_Texture* texture_{}; // ÎÆÀí

    HWND hwnd_{};
};