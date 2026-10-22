#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "defines.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} Platform;

Platform platform_init(const char* title, i32 window_width, i32 window_height, i32 texture_width, i32 texture_height); 
void platform_destroy(Platform* platform);

void platform_update(Platform* platform, void const* buffer, i32 pitch);
CEmulatorBool platform_process_input(u8* keys);

#endif // PLATFORM_H
