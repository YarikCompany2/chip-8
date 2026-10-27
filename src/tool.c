#include "tool.h"

#include <stdio.h>
#include <string.h>

void tool_chip8_memory_table_print(const Chip8* chip8) {
    printf("--- memory of the chip8 ---\n");
    
    for (i64 i = 0; i < MEMORY_SIZE; i++) {
        printf("%4.2x", chip8->memory[i]);
        if ((i + 1) % 20 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void tool_instruction_desc_get(u16 instruction, char *instruction_desc) {
    u16 first_sym = instruction & 0xF000;
    u16 last_sym = instruction & 0x000F;
    u16 third_sym = instruction & 0x00F0;
 
    switch (first_sym) {
        case 0x0000:
            switch (first_sym | third_sym | last_sym) {
                case 0x00e0:
                    sprintf(instruction_desc, "%.4X - chip8_op_00e0 - Clear the display", instruction);
                    return;
                case 0x00ee:
                    sprintf(instruction_desc, "%.4X - chip8_op_00ee - Return from a subroutine", instruction);
                    return;
                default:
                    sprintf(instruction_desc, "%.4X - instruction doesn't exist", instruction);
                    return;
            }
            return;

        case 0x1000:
            sprintf(instruction_desc, "%.4X - chip8_op_1nnn - Jump to location nnn", instruction);
            return;
        case 0x2000:
            sprintf(instruction_desc, "%.4X - chip8_op_2nnn - Call subroutine at nnn", instruction);
            return;
        case 0x3000:
            sprintf(instruction_desc, "%.4X - chip8_op_3xkk - Skip next instruction if registers[vx] == kk", instruction);
            return;
        case 0x4000:
            sprintf(instruction_desc, "%.4X - chip8_op_4xkk - Skip next instruction if registers[vx] != kk", instruction);
            return;
        case 0x5000:
            sprintf(instruction_desc, "%.4X - chip8_op_5xy0 - Skip next instruction if registers[vx] != registers[vy]", instruction);
            return;
        case 0x6000:
            sprintf(instruction_desc, "%.4X - chip8_op_6xkk - Set registers[vx] = kk", instruction);
            return;
        case 0x7000:
            sprintf(instruction_desc, "%.4X - chip8_op_7xkk - Set registers[vx] += kk", instruction);
            return;
        case 0x8000:
            switch (first_sym | last_sym) {
                case 0x8000:
                    sprintf(instruction_desc, "%.4X - chip8_op_8xy0 - Set registers[vx] = registers[vy]", instruction);
                    return;
                case 0x8001:
                    sprintf(instruction_desc, "%.4X - chip8_op_8xy1 - Set registers[vx] |= registers[vy]", instruction);
                    return;
                case 0x8002:
                    sprintf(instruction_desc, "%.4X - chip8_op_8xy2 - Set registers[vx] &= registers[vy]", instruction);
                    return;
                case 0x8003:
                    sprintf(instruction_desc, "%.4X - chip8_op_8xy3 - Set registers[vx] ^= registers[vy]", instruction);
                    return;
                case 0x8004:
                    sprintf(instruction_desc, "%.4X - chip8_op_8xy4 - Set registers[vx] += registers[vy], set registers[0xF] = carry", instruction);
                    return;
                case 0x8005:
                    sprintf(instruction_desc, "%.4X - chip8_op_8xy5 - Set registers[vx] -= registers[vy], set registers[0xF] = NOT borrow", instruction);
                    return;
                case 0x8006:
                    sprintf(instruction_desc, "%.4X - chip8_op_8xy6 - Set registers[vx] >>= 1, if the least-significant bit of Vx is 1, then registers[0xF] = 1", instruction);
                    return;
                case 0x8007:
                    sprintf(instruction_desc, "%.4X - chip8_op_8xy7 - Set registers[vx] = registers[vy] - registers[vx], set registers[0xF] = NOT borrow", instruction);
                    return;
                case 0x800e:
                    sprintf(instruction_desc, "%.4X - chip8_op_8xye - Set registers[vx] <<= 1, if the most-significant bit of registers[vx] is 1, then registers[0xF] = 1", instruction);
                    return;
                default:
                    sprintf(instruction_desc, "%.4X - instruction doesn't exist", instruction);
                    return;
            }
            return;

        case 0x9000:
            sprintf(instruction_desc, "%.4X - chip8_op_9xy0 - Skip next instruction if registers[vx] != registers[vy]", instruction);
            return;
        case 0xa000:
            sprintf(instruction_desc, "%.4X - chip8_op_annn - Set Index = nnn", instruction);
            return;
        case 0xb000:
            sprintf(instruction_desc, "%.4X - chip8_op_bnnn - Jump to location nnn + registers[0x0]", instruction);
            return;
        case 0xc000:
            sprintf(instruction_desc, "%.4X - chip8_op_cxkk - Set registers[vx] = random byte & nnn", instruction);
            return;
        case 0xd000:
            sprintf(instruction_desc, "%.4X - chip8_op_dxyn - Display n-byte sprite starting at memory location Index at (registers[vx], registers[vy]), set registers[0xF] = collision", instruction);
            return;
        case 0xe000:
            switch (first_sym | last_sym) {
                case 0xe00e:
                    sprintf(instruction_desc, "%.4X - chip8_op_ex9e - Skip next instruction if key with the value of registers[vx] is pressed", instruction);
                    return;
                case 0xe001:
                    sprintf(instruction_desc, "%.4X - chip8_op_exa1 - Skip next instruction if key with the value of registers[vx] is not pressed", instruction);
                    return;
                default:
                    sprintf(instruction_desc, "%.4X - instruction doesn't exist", instruction);
                    return;
            }
            return;
        
        case 0xf000:
            switch (first_sym | third_sym | last_sym) {
                case 0xf007:
                    sprintf(instruction_desc, "%.4X - chip8_op_fx07 - Set registers[vx] = delay timer value", instruction);
                    return;
                case 0xf00a:
                    sprintf(instruction_desc, "%.4X - chip8_op_fx0a - Wait for a key press, store the value of the key in registers[vx]", instruction);
                    return;
                case 0xf015:
                    sprintf(instruction_desc, "%.4X - chip8_op_fx15 - Set delay timer = registers[vx]", instruction);
                    return;
                case 0xf018:
                    sprintf(instruction_desc, "%.4X - chip8_op_fx18 - Set sound timer = registers[vx]", instruction);
                    return;
                case 0xf01e:
                    sprintf(instruction_desc, "%.4X - chip8_op_fx1e - Set Index += registers[vx]", instruction);
                    return;
                case 0xf029:
                    sprintf(instruction_desc, "%.4X - chip8_op_fx29 - Set Index = location of sprite for digit registers[vx]", instruction);
                    return;
                case 0xf033:
                    sprintf(instruction_desc, "%.4X - chip8_op_fx33 - Store BCD representation of registers[vx] in memory locations Index, Index+1, and Index+2", instruction);
                    return;
                case 0xf055:
                    sprintf(instruction_desc, "%.4X - chip8_op_fx55 - Store registers[0x0] through registers[vx] in memory starting at location Index", instruction);
                    return;
                case 0xf065:
                    sprintf(instruction_desc, "%.4X - chip8_op_fx65 - Read registers[0x0] through registers[vx] form memory starting at location Index", instruction);
                    return;
                default:
                    sprintf(instruction_desc, "%.4X - instruction doesn't exist", instruction);
                    return;
            }
            return;
        default:
            sprintf(instruction_desc, "%.4X - instruction doesn't exist", instruction);
            return;
    }
}

void tool_instruction_set_print(Chip8 *chip8, u32 rom_size) {
    char instruction_desc[200];
    u16 opcode = 0x0;

    for (u32 i = START_ADDRESS; i < START_ADDRESS + rom_size; i += 2) {
        opcode = chip8->memory[i] << 8 | chip8->memory[i+1];

        tool_instruction_desc_get(opcode, instruction_desc);
        printf("$%.4X -> %s\n", i, instruction_desc);
    }
}