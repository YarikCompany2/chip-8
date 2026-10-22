#include "platform.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

Platform platform_init(const char* title, i32 window_width, i32 window_height, i32 texture_width, i32 texture_height) {
    SDL_Init(SDL_INIT_VIDEO);

    Platform platform;

    platform.window = SDL_CreateWindow(title, 0, 0, window_width, window_height, SDL_WINDOW_SHOWN);
    platform.renderer = SDL_CreateRenderer(platform.window, -1, SDL_RENDERER_ACCELERATED);
    platform.texture = SDL_CreateTexture(platform.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, texture_width, texture_height);

    return platform;
}

void platform_destroy(Platform* platform) {
    SDL_DestroyTexture(platform->texture);
    SDL_DestroyRenderer(platform->renderer);
    SDL_DestroyWindow(platform->window);
    SDL_Quit();
}

void platform_update(Platform* platform, void const* buffer, i32 pitch) {
    SDL_UpdateTexture(platform->texture, NULL, buffer, pitch);
    SDL_RenderClear(platform->renderer);
    SDL_RenderCopy(platform->renderer, platform->texture, NULL, NULL);
    SDL_RenderPresent(platform->renderer);
}

CEmulatorBool platform_process_input(u8* keys) {
    CEmulatorBool quit = CEMULATOR_FALSE;

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = CEMULATOR_TRUE;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = CEMULATOR_TRUE;
                        break;
                    case SDLK_x:
                        keys[0] = 1;
                        break;
                    case SDLK_1:
                        keys[1] = 1;
                        break;
                    case SDLK_2:
                        keys[2] = 1;
                        break;
                    case SDLK_3:
                        keys[3] = 1;
                        break;
                    case SDLK_q:
                        keys[4] = 1;
                        break;
                    case SDLK_w:
                        keys[5] = 1;
                        break;
                    case SDLK_e:
                        keys[6] = 1;
                        break;
                    case SDLK_a:
                        keys[7] = 1;
                        break;
                    case SDLK_s:
                        keys[8] = 1;
                        break;
                    case SDLK_d:
                        keys[9] = 1;
                        break;
                    case SDLK_z:
                        keys[0xA] = 1;
                        break;
                    case SDLK_c:
                        keys[0xB] = 1;
                        break;
                    case SDLK_4:
                        keys[0xC] = 1;
                        break;
                    case SDLK_r:
                        keys[0xD] = 1;
                        break;
                    case SDLK_f:
                        keys[0xE] = 1;
                        break;
                    case SDLK_v:
                        keys[0xF] = 1;
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = CEMULATOR_TRUE;
                        break;
                    case SDLK_x:
                        keys[0] = 0;
                        break;
                    case SDLK_1:
                        keys[1] = 0;
                        break;
                    case SDLK_2:
                        keys[2] = 0;
                        break;
                    case SDLK_3:
                        keys[3] = 0;
                        break;
                    case SDLK_q:
                        keys[4] = 0;
                        break;
                    case SDLK_w:
                        keys[5] = 0;
                        break;
                    case SDLK_e:
                        keys[6] = 0;
                        break;
                    case SDLK_a:
                        keys[7] = 0;
                        break;
                    case SDLK_s:
                        keys[8] = 0;
                        break;
                    case SDLK_d:
                        keys[9] = 0;
                        break;
                    case SDLK_z:
                        keys[0xA] = 0;
                        break;
                    case SDLK_c:
                        keys[0xB] = 0;
                        break;
                    case SDLK_4:
                        keys[0xC] = 0;
                        break;
                    case SDLK_r:
                        keys[0xD] = 0;
                        break;
                    case SDLK_f:
                        keys[0xE] = 0;
                        break;
                    case SDLK_v:
                        keys[0xF] = 0;
                        break;
                }
                break;
        }
    }

    return quit;
}
