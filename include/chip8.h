#ifndef CHIP8_H
#define CHIP8_H

#define REGISTERS_SIZE 16
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define KEYPAD_AMOUNT 16
#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32

#define START_ADDRESS 0x200

#define FONTSET_SIZE 80
#define FONTSET_START_ADDRESS 0x50

#include <stdint.h>
#include "defines.h"

typedef struct {
    u8 registers[REGISTERS_SIZE];
    u8 memory[MEMORY_SIZE];
    u16 index;
    u16 pc;
    u16 stack[STACK_SIZE];
    u8 sp;
    u8 delayTimer;
    u8 soundTimer;
    u8 keypad[KEYPAD_AMOUNT];
    u32 video[VIDEO_WIDTH * VIDEO_HEIGHT];
    u16 opcode;
} Chip8;

Chip8 chip8_init();
CEMULATOR_BOOL chip8_load_rom(Chip8* chip8, char const* filename);

// Instructions
void chip8_op_00e0(Chip8* chip8); // CLS: Clear the display
void chip8_op_00ee(Chip8* chip8); // RET: Return from a subroutine
void chip8_op_1nnn(Chip8* chip8); // JP addr: Jump to location nnn
void chip8_op_2nnn(Chip8* chip8); // CALL addr: Call subroutine at nnn
void chip8_op_3xkk(Chip8* chip8); // SE Vx, byte: Skip next instruction if Vx = kk
void chip8_op_4xkk(Chip8* chip8); // SNE Vx, byte: Skip next instruction if Vx != kk



void chip8_print_memory_table(const Chip8* chip8);



#endif // CHIP8_H