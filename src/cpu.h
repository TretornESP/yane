#ifndef _CPU_H
#define _CPU_H

#define CARRY 0x0
#define ZERO 0x1
#define INTERRUPT 0x2
#define DECIMAL 0x3
#define BREAK 0x4
#define UNUSED 0x5
#define OVERFLOW 0x6
#define NEGATIVE 0x7

#define IMMEDIATE       0x01
#define ZERO_PAGE      0x02
#define ZERO_PAGE_X    0x03
#define ZERO_PAGE_Y    0x04
#define ABSOLUTE       0x05
#define ABSOLUTE_X     0x06
#define ABSOLUTE_Y     0x07
#define INDIRECT_X     0x08
#define INDIRECT_Y     0x09
#define NONE           0x0A
#define IMPLIED        0x0B
#define ACCUMULATOR    0x0C
#define INDIRECT       0x0D
#define RELATIVE       0x0E

#include <stdint.h>
#include "memory.h"

struct sr {
    uint8_t c:1;
    uint8_t z:1;
    uint8_t i:1;
    uint8_t d:1;
    uint8_t b:1;
    uint8_t u:1;
    uint8_t v:1;
    uint8_t n:1;
} __attribute__((packed));

union sr_union {
    struct sr sr;
    uint8_t sr_byte;
};

struct registers {
    uint16_t pc;
    uint8_t sp;
    uint8_t a;
    uint8_t x;
    uint8_t y;
    union sr_union flags;
} __attribute__((packed));

struct cpu { //TODO
    struct registers regs;
    union memory_union* mem;
    uint8_t cycles;
    uint8_t opcode;
    uint8_t operand;
    uint8_t addr_mode;
    uint16_t return_address;
    uint8_t cross_page_cycles;
    uint8_t page_boundary_crossed;
    uint8_t stack_top;
    uint8_t irq;
    uint8_t nmi;
    uint8_t reset;
    uint8_t debug;
};

uint8_t get_flag(struct cpu *cpu, uint8_t flag);
void set_flag(struct cpu *cpu, uint8_t flag, uint8_t value);
uint8_t get_flags(struct cpu *cpu);
void set_flags(struct cpu *cpu, uint8_t value);

void set_pc(struct cpu *cpu, uint16_t address);
void set_sp(struct cpu *cpu, uint8_t value);
void set_a(struct cpu *cpu, uint8_t value);
void set_x(struct cpu *cpu, uint8_t value);
void set_y(struct cpu *cpu, uint8_t value);

void push(struct cpu *cpu, uint8_t value);
uint8_t pull(struct cpu *cpu);

uint16_t get_pc(struct cpu *cpu);
uint8_t get_sp(struct cpu *cpu);
uint8_t get_a(struct cpu *cpu);
uint8_t get_x(struct cpu *cpu);
uint8_t get_y(struct cpu *cpu);

union memory_union* get_mem(struct cpu *cpu);

void cpu_init(struct cpu *cpu, union memory_union* mem);
void cpu_act(struct cpu* cpu, uint8_t debug);
void cpu_reset(struct cpu *cpu);

void cpu_set_return_addr(struct cpu *cpu, uint16_t address);
uint16_t cpu_get_return_addr(struct cpu *cpu);
#endif