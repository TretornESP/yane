#ifndef _ISET_H
#define _ISET_H
#include "cpu.h"

#define ISET_SIZE      256

struct instruction {
    uint8_t opcode;
    char name[4];
    uint8_t bytes;
    uint8_t cycles;
    uint8_t addr_mode;
    uint8_t cross_page_cycles;
    void (*execute)(struct cpu *cpu, uint16_t address);
};

extern struct instruction iset[ISET_SIZE];

struct instruction * get_instruction(uint8_t opcode);
void dissasemble(uint8_t *memory, uint16_t address, uint32_t length);
#endif