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
    u8 delay_timer;
    u8 sound_timer;
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
void chip8_op_5xy0(Chip8* chip8); // SE Vx, Vy: Skip next instruction if Vx = Vy
void chip8_op_6xkk(Chip8* chip8); // LD Vx, byte: Set Vx = kk
void chip8_op_7xkk(Chip8* chip8); // ADD Vx, byte: Set Vx = Vx + kk
void chip8_op_8xy0(Chip8* chip8); // LD Vx, Vy: Set Vx = Vy
void chip8_op_8xy1(Chip8* chip8); // OR Vx, Vy: Set Vx = Vx OR Vy
void chip8_op_8xy2(Chip8* chip8); // AND Vx, Vy: Set Vx = Vx AND Vy
void chip8_op_8xy3(Chip8* chip8); // XOR Vx, Vy: Set Vx = Vx XOR Vy
void chip8_op_8xy4(Chip8* chip8); // ADD Vx, Vy: Set Vx = Vx + Vy, set VF = carry
void chip8_op_8xy5(Chip8* chip8); // SUB Vx, Vy: Set Vx = Vx - Vy, set VF = NOT borrow
void chip8_op_8xy6(Chip8* chip8); // SHR Vx
void chip8_op_8xy7(Chip8* chip8); // SUBN Vx, Vy: Set Vx = Vy - Vx, set VF = NOT borrow
void chip8_op_8xye(Chip8* chip8); // SHL Vx {, Vy}: Set Vx = Vx SHL 1
void chip8_op_9xy0(Chip8* chip8); // SNE Vx, Vy: Skip next instruction if Vx != Vy
void chip8_op_annn(Chip8* chip8); // LD I, addr: Set I = nnn
void chip8_op_bnnn(Chip8* chip8); // JP V0, addr: Jump to location nnn + V0
void chip8_op_cxkk(Chip8* chip8); // RND Vx, byte: Set Vx = random byte AND kk
void chip8_op_dxyn(Chip8* chip8); // DRW Vx, Vy, nibble
void chip8_op_ex9e(Chip8* chip8); // SKP Vx: Skip next instruction if key with the value of Vx is pressed
void chip8_op_exa1(Chip8* chip8); // SKNP Vx: Skip next instruction if key with the value of Vx is not pressed 
void chip8_op_fx07(Chip8* chip8); // LD Vx, DT: Set Vx = delay timer value
void chip8_op_fx0a(Chip8* chip8); // LD Vx, K: Wait for a key press, store the value of the key in Vx
void chip8_op_fx15(Chip8* chip8); // LD DT, Vx: Set delay timer = Vx
void chip8_op_fx18(Chip8* chip8); // LD ST, Vx: Set sound timer = Vx
void chip8_op_fx1e(Chip8* chip8); // ADD I, Vx: Set I = I + Vx
void chip8_op_fx29(Chip8* chip8); // LD F, Vx: Set I = location of sprite for digit Vx
void chip8_op_fx33(Chip8* chip8); // LD B, Vx: Store BCD representation of Vx in memory locations I, I+1, and I+2
void chip8_op_fx55(Chip8* chip8); // LD [I] Vx: Store registers V0 through Vx in memory starting at location I
void chip8_op_fx65(Chip8* chip8); // LD Vx, [I]: Read registers V0 through Vx form memory starting at location I

void chip8_print_memory_table(const Chip8* chip8);

#endif // CHIP8_H
