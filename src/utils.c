#include "utils.h" 
 
void utils_string_slice(char *string, u32 start, u32 end, char *slice) {
    u32 string_size = strlen(string);

    if (string_size >= end || end == 0) {
        end = string_size;
    }

    for (u32 i = start, j = 0; i < end; i++, j++) {
        slice[j] = string[i];
    }

    slice[end - start] = '\0';
}