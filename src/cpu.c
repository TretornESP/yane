#include "cpu.h"
#include "iset.h"
#include "memory.h"
#include "logs.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t get_flag(struct cpu *cpu, uint8_t flag) {
    uint8_t regs = cpu->regs.flags.sr_byte;
    return (regs >> flag) & 1;
}

void set_flag(struct cpu *cpu, uint8_t flag, uint8_t value) {
    uint8_t  regs = cpu->regs.flags.sr_byte;
    if (value) {
        regs |= (1 << flag);
    } else {
        regs &= ~(1 << flag);
    }
    cpu->regs.flags.sr_byte = regs;
}

void set_pc(struct cpu *cpu, uint16_t address) {
    cpu->regs.pc = address;
}
void set_sp(struct cpu *cpu, uint8_t value) {
    cpu->regs.sp = value;
}
void set_a(struct cpu *cpu, uint8_t value) {
    cpu->regs.a = value;
}
void set_x(struct cpu *cpu, uint8_t value) {
    cpu->regs.x = value;
}
void set_y(struct cpu *cpu, uint8_t value) {
    cpu->regs.y = value;
}

uint16_t get_pc(struct cpu *cpu) {
    return cpu->regs.pc;
}

uint8_t get_sp(struct cpu *cpu) {
    return cpu->regs.sp;
}

uint8_t get_a(struct cpu *cpu) {
    return cpu->regs.a;
}

uint8_t get_x(struct cpu *cpu) {
    return cpu->regs.x;
}

uint8_t get_y(struct cpu *cpu) {
    return cpu->regs.y;
}

void dump_cpu(struct cpu *cpu) {
    printf("PC: 0x%04X SP: 0x%02X\n", cpu->regs.pc, cpu->regs.sp);
    printf("A: 0x%02X X: 0x%02X Y: 0x%02X\n", cpu->regs.a, cpu->regs.x, cpu->regs.y);
    for (int i = 0; i < 8; i++) {
        printf("%d", cpu->regs.flags.sr_byte & (1 << i));
    }
    printf("\nCZIDB-VN\n");
}

void cpu_act(struct cpu* cpu, uint8_t debug) {
    //Instruction execute
    if (debug) {
        dump_cpu(cpu);
    }

    //Instruction fetch
    uint8_t opcode = memory_read(cpu->mem, cpu->regs.pc);
    cpu->regs.pc++;

    //Instruction decode
    struct instruction* inst = get_instruction(opcode);

    uint16_t effective_address;
    switch (inst->addr_mode) {
        case ABSOLUTE: {
            uint16_t addr = memory_read_word(cpu->mem, cpu->regs.pc);
            cpu->regs.pc += 2;
            effective_address = addr;
            break;
        }
        case ABSOLUTE_X: {
            uint16_t addr = memory_read_word(cpu->mem, cpu->regs.pc);
            cpu->regs.pc += 2;
            effective_address = addr + cpu->regs.x;
            break;
        }
        case ABSOLUTE_Y: {
            uint16_t addr = memory_read_word(cpu->mem, cpu->regs.pc);
            cpu->regs.pc += 2;
            effective_address = addr + cpu->regs.y;
            break;
        }
        case ACCUMULATOR: {
            effective_address = 0;
            break;
        }
        case IMMEDIATE: {
            effective_address = cpu->regs.pc;
            cpu->regs.pc++;
            break;
        }
        case IMPLIED: {
            effective_address = 0;
            break;
        }
        case INDIRECT: {
            uint16_t addr = memory_read_word(cpu->mem, cpu->regs.pc);
            cpu->regs.pc += 2;
            effective_address = memory_read_word(cpu->mem, addr);
            break;
        }
        case INDIRECT_X: {
            uint8_t addr = memory_read(cpu->mem, cpu->regs.pc);
            cpu->regs.pc++;
            effective_address = memory_read_word(cpu->mem, addr + cpu->regs.x);
            break;
        }
        case INDIRECT_Y: {
            uint8_t addr = memory_read(cpu->mem, cpu->regs.pc);
            cpu->regs.pc++;
            effective_address = memory_read_word(cpu->mem, addr) + cpu->regs.y;
            break;
        }
        case RELATIVE: {
            uint8_t addr = memory_read(cpu->mem, cpu->regs.pc);
            cpu->regs.pc++;
            effective_address = cpu->regs.pc + addr;
            break;
        }
        case ZERO_PAGE: {
            uint8_t addr = memory_read(cpu->mem, cpu->regs.pc);
            cpu->regs.pc++;
            effective_address = addr;
            break;
        }
        case ZERO_PAGE_X: {
            uint8_t addr = memory_read(cpu->mem, cpu->regs.pc);
            cpu->regs.pc++;
            effective_address = addr + cpu->regs.x;
            break;
        }
        case ZERO_PAGE_Y: {
            uint8_t addr = memory_read(cpu->mem, cpu->regs.pc);
            cpu->regs.pc++;
            effective_address = addr + cpu->regs.y;
            break;
        }
        default: {
            printf("Unknown addressing mode\n");
            exit(1);
        }
    }

    if (debug) {
        printf("INST: %s 0x%04X\n", inst->name, effective_address);
        printf("--------------------\n");
    }

    inst->execute(cpu, effective_address);

}

void cpu_init(struct cpu *cpu, union memory_union* mem) {
    cpu->mem = mem;
    cpu->regs.pc = 0;
    cpu->regs.sp = 0;
    cpu->regs.a = 0;
    cpu->regs.x = 0;
    cpu->regs.y = 0;
    cpu->regs.flags.sr_byte = 0;

    cpu->regs.pc = memory_read_word(cpu->mem, 0xFFFC);

    cpu->regs.sp = 0xEF;
}

void cpu_reset(struct cpu *cpu) {
    cpu->regs.pc = memory_read_word(cpu->mem, 0xFFFC);
    cpu->regs.sp = 0xEF;
    cpu->regs.a = 0;
    cpu->regs.x = 0;
    cpu->regs.y = 0;
    cpu->regs.flags.sr_byte = 0;
}

void push(struct cpu *cpu, uint8_t value) {
    memory_write(cpu->mem, 0x100 + cpu->regs.sp, value);
    cpu->regs.sp--;
}

uint8_t pull(struct cpu *cpu) {
    cpu->regs.sp++;
    return memory_read(cpu->mem, 0x100 + cpu->regs.sp);
}

uint8_t get_flags(struct cpu *cpu) {
    return cpu->regs.flags.sr_byte;
}

void set_flags(struct cpu *cpu, uint8_t flags) {
    cpu->regs.flags.sr_byte = flags;
}

union memory_union* get_mem(struct cpu *cpu) {
    return cpu->mem;
}