#include "chip8.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

static const u8 fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8 chip8_init() {
    Chip8 chip8 = {0};

    chip8.pc = START_ADDRESS;

    for (u32 i = 0; i < FONTSET_SIZE; i++) {
        chip8.memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }

    return chip8;
}

CEMULATOR_BOOL chip8_load_rom(Chip8* chip8, char const* filename) {
    FILE* file = fopen(filename, "rb");

    if (!file) {
        printf("Can't open file %s, maybe the name is incorrect", filename);
        return CEMULATOR_FALSE;
    }

    fseek(file, 0, SEEK_END);

    u32 file_size = ftell(file);
    printf("file size: %d\n", file_size);

    char* buffer = malloc(sizeof(char) * file_size);

    rewind(file);
    fread(buffer, sizeof(char), file_size, file);
    fclose(file);

    for (i64 i = 0; i < file_size; i++) {
        chip8->memory[START_ADDRESS + i] = buffer[i];
    }

    free(buffer);
    return CEMULATOR_TRUE;
}

void chip8_op_00e0(Chip8* chip8) {
    memset(chip8->video, 0, sizeof(chip8->video));
}

void chip8_op_00ee(Chip8* chip8) {
    --chip8->sp;
    chip8->pc = chip8->stack[chip8->sp];
}

void chip8_print_memory_table(const Chip8* chip8) {
    printf("--- memory of the chip8 ---\n");
    
    for (i64 i = 0; i < MEMORY_SIZE; i++) {
        printf("%4d", chip8->memory[i]);
        if ((i + 1) % 20 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}
