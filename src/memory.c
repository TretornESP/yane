#include "memory.h"
#include "logs.h"

#define OOB(addr) ((addr >= (MEMORY_SIZE-1)) ? dbg(__FILE__, "Out of bounds memory access at 0x%04X MAX:%04X", addr, MEMORY_SIZE) : 0)

void memory_init(union memory_union* memory) {
    memory_reset(memory);
}

void memory_reset(union memory_union* memory) {
    for (uint16_t i = 0; i < (MEMORY_SIZE-1); i++) {
        memory->raw[i] = 0;
    }
}

void memory_set_prg_rom(union memory_union* memory, uint8_t* rom, uint16_t rom_size) {
    for (uint16_t i = 0; i < rom_size; i++) {
        memory->mem.prg_rom[i] = rom[i];
    }
}

void memory_set_at(union memory_union* memory, uint16_t addr, uint8_t *data, uint16_t size) {
    for (uint16_t i = 0; i < size; i++) {
        memory->raw[addr + i] = data[i];
    }
}

void memory_set_startup_vector(union memory_union* memory, uint16_t startup_vector) {
    memory->raw[0xFFFC] = startup_vector & 0xFF;
    memory->raw[0xFFFD] = startup_vector >> 8;
}

uint8_t memory_read_silent(union memory_union* memory, uint16_t addr) {
    OOB(addr);
    return memory->raw[addr];
}

void memory_write_silent(union memory_union* memory, uint16_t addr, uint8_t data) {
    OOB(addr);
    memory->raw[addr] = data;
}

uint8_t memory_read(union memory_union* memory, uint16_t addr) {
    OOB(addr);
    printf("R [0x%04X] => 0x%02X\n", addr, memory->raw[addr]);
    return memory->raw[addr];
}

void memory_write(union memory_union* memory, uint16_t addr, uint8_t data) {
    OOB(addr);
    printf("W [0x%04X] <= 0x%02X\n", addr, data);
    memory->raw[addr] = data;
}

uint16_t memory_read_word(union memory_union* memory, uint16_t addr) {
    OOB(addr + 1);
    printf("R(W) [0x%04X] => 0x%04X\n", addr, memory->raw[addr] | (memory->raw[addr + 1] << 8));
    return memory->raw[addr] | (memory->raw[addr + 1] << 8);
}

uint16_t memory_read_word_silent(union memory_union* memory, uint16_t addr) {
    OOB(addr + 1);
    return memory->raw[addr] | (memory->raw[addr + 1] << 8);
}

void memory_write_word(union memory_union* memory, uint16_t addr, uint16_t data) {
    OOB(addr + 1);
    printf("W(W) [0x%04X] <= 0x%04X\n", addr, data);
    memory->raw[addr] = data & 0xFF;
    memory->raw[addr + 1] = data >> 8;
}

void memory_write_word_silent(union memory_union* memory, uint16_t addr, uint16_t data) {
    OOB(addr + 1);
    memory->raw[addr] = data & 0xFF;
    memory->raw[addr + 1] = data >> 8;
}

uint8_t memory_read_relative(union memory_union* memory, uint16_t addr, uint8_t offset) {
    OOB(addr + offset);
    return memory->raw[addr + offset];
}

void memory_write_relative(union memory_union* memory, uint16_t addr, uint8_t offset, uint8_t data) {
    OOB(addr + offset);
    memory->raw[addr + offset] = data;
}