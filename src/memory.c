#include "memory.h"
#include "logs.h"

#define OOB(addr) ((addr >= MEMORY_SIZE) ? dbg(__FILE__, "Out of bounds memory access at 0x%04X", addr) : 0)

union memory_union memory = {0};

void memory_init() {
    memory_reset();
}

void memory_reset() {
    for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
        memory.raw[i] = 0;
    }
}

uint8_t memory_read(uint16_t addr) {
    OOB(addr);
    return memory.raw[addr];
}

void memory_write(uint16_t addr, uint8_t data) {
    OOB(addr);
    memory.raw[addr] = data;
}

uint8_t memory_read_relative(uint16_t addr, uint8_t offset) {
    OOB(addr + offset);
    return memory.raw[addr + offset];
}

void memory_write_relative(uint16_t addr, uint8_t offset, uint8_t data) {
    OOB(addr + offset);
    memory.raw[addr + offset] = data;
}