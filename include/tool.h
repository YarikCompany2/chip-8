#ifndef TOOL_H
#define TOOL_H

#include <stdio.h>

#include "chip8.h"
#include "defines.h"

typedef enum {
    TOOL_PRINT_MEMORY_TABLE,
    TOOL_PRINT_INSTRUCTION_SET,
    TOOL_UNSPECIFIED,
} ToolType;

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


void tool_instruction_set_print(Chip8* chip8) {
    chip8->mode = CHIP8_PRINT_INSTRUCTIONS_MODE;

    while (CEMULATOR_TRUE) {
        chip8_cycle(chip8);
    }
}

#endif // TOOL_H
