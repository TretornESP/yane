#include <stdio.h>
#include "../memory.h"

int memory_tests() {
    printf("[MEMORY TESTS STARTING]\n");
    memory_init();
    memory_reset();

    for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
        if (memory_read(i) != 0) {
            printf("memory_read() failed at 0x%04X\n", i);
            return 1;
        }
    }

    for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
        memory_write(i, 0xFF);
        if (memory_read(i) != 0xFF) {
            printf("memory_write() failed at 0x%04X\n", i);
            return 1;
        }
    }

    for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
        memory_write(i, 0x00);
        memory_write_relative(i, 0, 0xFF);
        if (memory_read(i) != 0xFF) {
            printf("memory_write_relative() failed at 0x%04X\n", i);
            return 1;
        }
    }

    for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
        memory_write(i, 0x00);
        memory_write_relative(i, 0, 0xFF);
        if (memory_read_relative(i, 0) != 0xFF) {
            printf("memory_read_relative() failed at 0x%04X\n", i);
            return 1;
        }
    }

    printf("[MEMORY TESTS PASSED]\n");
    return 0;
}