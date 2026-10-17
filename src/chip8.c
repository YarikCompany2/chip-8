#include "chip8.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    srand(time(0));

    return chip8;
}

// Generate byte from 0 to 255
u8 get_rand_byte() {
    return (u8)rand() % (255u + 1u); 
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

void chip8_op_1nnn(Chip8* chip8) {
    u16 address = chip8->opcode & 0x0FFFu;

    chip8->pc = address;
}

void chip8_op_2nnn(Chip8* chip8) {
    u16 address = chip8->opcode & 0x0FFFu;

    chip8->stack[chip8->sp] = chip8->pc;
    chip8->sp++;

    chip8->pc = address;
}

void chip8_op_3xkk(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 byte = chip8->opcode & 0x00FFu;

    if (chip8->registers[vx] == byte)
        chip8->pc += 2;
}

void chip8_op_4xkk(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 byte = chip8->opcode & 0x00FFu;

    if (chip8->registers[vx] != byte)
        chip8->pc += 2;
}

void chip8_op_5xy0(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;

    if (chip8->registers[vx] == chip8->registers[vy])
        chip8->pc += 2;
}

void chip8_op_6xkk(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 byte = chip8->opcode & 0x00FFu;

    chip8->registers[vx] = byte;
}

void chip8_op_7xkk(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 byte = chip8->opcode & 0x00FFu;

    chip8->registers[vx] += byte;
}

void chip8_op_8xy0(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;

    chip8->registers[vx] = chip8->registers[vy];
}

void chip8_op_8xy1(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;

    chip8->registers[vx] |= chip8->registers[vy];
}

void chip8_op_8xy2(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;

    chip8->registers[vx] &= chip8->registers[vy];
}

void chip8_op_8xy3(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;

    chip8->registers[vx] ^= chip8->registers[vy];
}

void chip8_op_8xy4(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;

    u16 sum = chip8->registers[vx] + chip8->registers[vy];

    if (sum > 0xFFu)
        chip8->registers[0xF] = 1;
    else
        chip8->registers[0xF] = 0;

    chip8->registers[vx] = sum & 0xFFu;
}

void chip8_op_8xy5(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;

    if (chip8->registers[vx] > chip8->registers[vy])
        chip8->registers[0xF] = 1;
    else
        chip8->registers[0xF] = 0;

    chip8->registers[vx] -= chip8->registers[vy];
}

void chip8_op_8xy6(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;

    chip8->registers[0xF] = (chip8->registers[vx] & 0x1u);

    chip8->registers[vx] >>= 1;
}

void chip8_op_8xy7(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;

    if (chip8->registers[vy] > chip8->registers[vx])
        chip8->registers[0xF] = 1;
    else
        chip8->registers[0xF] = 0;

    chip8->registers[vx] = chip8->registers[vy] - chip8->registers[vx];
}

void chip8_op_8xye(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;

    chip8->registers[0xF] = (chip8->registers[vx] & 0x80u) >> 7u;

    chip8->registers[vx] <<= 1;
}

void chip8_op_9xy0(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;

    if (chip8->registers[vx] != chip8->registers[vy])
        chip8->pc += 2;
}

void chip8_op_annn(Chip8* chip8) {
    u16 address = chip8->opcode & 0x0FFFu;
    
    chip8->index = address;
}

void chip8_op_bnnn(Chip8* chip8) {
    u16 address = chip8->opcode & 0x0FFFu;

    chip8->pc = address + chip8->registers[0x0];
}

void chip8_op_cxkk(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;

    u8 byte = chip8->opcode & 0x00FFu;
    u8 rand_byte = get_rand_byte();
    
    chip8->registers[vx] = rand_byte & byte;
}

void chip8_op_dxyn(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 vy = (chip8->opcode & 0x00F0u) >> 4u;
    u8 height = chip8->opcode & 0x000Fu;

    u8 x_pos = chip8->registers[vx] % VIDEO_WIDTH;
    u8 y_pos = chip8->registers[vy] % VIDEO_HEIGHT;

    chip8->registers[0xF] = 0;

    for (u32 i = 0; i < height; i++) {
        u8 sprite_byte = chip8->memory[chip8->index + i];

        for (u32 j = 0; j < 8; j++) {
            u8 sprite_pixel = sprite_byte & (0x80u >> j);
            u32* screen_pixel = &chip8->video[(y_pos + i) * VIDEO_WIDTH + (x_pos + j)];

            if (sprite_pixel) {
                if (*screen_pixel == 0xFFFFFFFF)
                    chip8->registers[0xF] = 1;

                *screen_pixel ^= 0xFFFFFFFF;
            }
        }
    }
}

void chip8_op_ex9e(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 key = chip8->registers[vx];

    if (chip8->keypad[key])
        chip8->pc += 2;
}

void chip8_op_exa1(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;
    u8 key = chip8->registers[vx];

    if (!chip8->keypad[key])
        chip8->pc += 2;
}

void chip8_op_fx07(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;

    chip8->registers[vx] = chip8->delay_timer;
}

void chip8_op_fx0a(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) > 8u;
    
    for (u32 i = 0; i < KEYPAD_AMOUNT; i++) {
        if (chip8->keypad[i]) {
            chip8->registers[vx] = i;
            return;
        }
    }

    chip8->pc -= 2;
}

void chip8_op_fx15(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;

    chip8->delay_timer = chip8->registers[vx];
}

void chip8_op_fx18(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;

    chip8->sound_timer = chip8->registers[vx];
}

void chip8_op_fx1e(Chip8* chip8) {
    u8 vx = (chip8->opcode & 0x0F00u) >> 8u;

    chip8->index += chip8->registers[vx];
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
