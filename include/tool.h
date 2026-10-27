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

void tool_chip8_memory_table_print(const Chip8* chip8);

void tool_instruction_desc_get(u16 instruction, char *instruction_desc);
void tool_instruction_set_print(Chip8* chip8, u32 rom_size);

#endif // TOOL_H
