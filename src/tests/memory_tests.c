#include <stdio.h>
#include "../memory.h"

int memory_tests() {
    printf("[MEMORY TESTS STARTING]\n");
    union memory_union memory = {0};

    memory_init(&memory);
    memory_reset(&memory);

    for (uint16_t i = 0; i < (MEMORY_SIZE-1); i++) {
        if (memory_read(&memory, i) != 0) {
            printf("memory_read() failed at 0x%04X\n", i);
            return 1;
        }
    }

    for (uint16_t i = 0; i < (MEMORY_SIZE-1); i++) {
        memory_write(&memory, i, 0xFF);
        if (memory_read(&memory, i) != 0xFF) {
            printf("memory_write() failed at 0x%04X\n", i);
            return 1;
        }
    }

    for (uint16_t i = 0; i < (MEMORY_SIZE-1); i++) {
        memory_write(&memory, i, 0x00);
        memory_write_relative(&memory, i, 0, 0xFF);
        if (memory_read(&memory, i) != 0xFF) {
            printf("memory_write_relative() failed at 0x%04X\n", i);
            return 1;
        }
    }

    for (uint16_t i = 0; i < (MEMORY_SIZE-1); i++) {
        memory_write(&memory, i, 0x00);
        memory_write_relative(&memory, i, 0, 0xFF);
        if (memory_read_relative(&memory, i, 0) != 0xFF) {
            printf("memory_read_relative() failed at 0x%04X\n", i);
            return 1;
        }
    }

    printf("[MEMORY TESTS PASSED]\n");
    return 0;
}