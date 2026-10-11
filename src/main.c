#include "chip8.h"
#include <stdio.h>

int main(void) {
    Chip8 chip8 = chip8_init();

    if (!chip8_load_rom(&chip8, "test_file.txt")) return 1;

    chip8_print_memory_table(&chip8);

    return 0;
}