#include "chip8.h"
#include "platform.h"
#include "tool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    ToolType tool_type = TOOL_UNSPECIFIED;
    i32 filename_index = 3;

    if (argc == 3) {
        if (strcmp(argv[1], "-t") == 0)
            tool_type = TOOL_PRINT_MEMORY_TABLE;
        else if (strcmp(argv[1], "-i") == 0)
            tool_type = TOOL_PRINT_INSTRUCTION_SET;
        else {
            printf("Uknown flag is presented. If you want to use program with the flage, use: %s <tool> <game_path>\n", argv[0]);
            printf("Otherwise, if you want to launch emulator to play, use: %s <scale> <delay> <game_path>\n", argv[0]);
            return 1;
        }

        filename_index = 2;
    } else if (argc != 4) {
        printf("To use this program, write: %s <scale> <delay> <game_path>\n", argv[0]);
        return 1;
    }

    char const* rom_filename = argv[filename_index];

    Chip8 chip8 = chip8_init();
    if (!chip8_rom_load(&chip8, rom_filename)) return 1;

    switch (tool_type) {
        case TOOL_PRINT_MEMORY_TABLE:
            tool_chip8_memory_table_print(&chip8);
            return 0;
        case TOOL_PRINT_INSTRUCTION_SET:
            tool_instruction_set_print(&chip8);
            return 0;
        default:
            break;
    }

    u32 video_scale = atoi(argv[1]);
    u32 cycle_delay = atoi(argv[2]);

    Platform platform = platform_init("CEmulator", VIDEO_WIDTH * video_scale, VIDEO_HEIGHT * video_scale, VIDEO_WIDTH, VIDEO_HEIGHT);

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

    return 0;
}
