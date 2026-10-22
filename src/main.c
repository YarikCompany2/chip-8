#include "chip8.h"
#include "platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("To use this program, write: %s <scale> <delay> <game_path>\n", argv[0]);
        return 1;
    }

    u32 video_scale = atoi(argv[1]);
    u32 cycle_delay = atoi(argv[2]);
    char const* rom_filename = argv[3];

    Platform platform = platform_init("CEmulator", VIDEO_WIDTH * video_scale, VIDEO_HEIGHT * video_scale, VIDEO_WIDTH, VIDEO_HEIGHT);

    Chip8 chip8 = chip8_init();
    chip8_rom_load(&chip8, rom_filename);

    i32 video_pitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

    clock_t last_cycle_time = clock();
    CEmulatorBool quit = CEMULATOR_FALSE;

    while (!quit) {
        quit = platform_process_input(chip8.keypad);

        clock_t current_time = clock();
        float dt = (float)(current_time - last_cycle_time) * 1000.0f / (float)CLOCKS_PER_SEC;

        if (dt > cycle_delay) {
            last_cycle_time = current_time;
            chip8_cycle(&chip8);
            platform_update(&platform, chip8.video, video_pitch);
        }
    }

    platform_destroy(&platform);
    // chip8_print_memory_table(&chip8);

    return 0;
}
