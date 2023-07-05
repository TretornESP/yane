#include "iset.h"
#include "memory.h"
#include "logs.h"
#include <stdio.h>
#include <stdlib.h>

//https://github.com/bugzmanov/nes_ebook/blob/master/code/ch3.3/src/cpu.rs

void adc(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t a_value = get_a(cpu);
    uint16_t result = a_value + value + get_flag(cpu, CARRY);

    set_flag(cpu, CARRY, result > 0xFF);
    set_flag(cpu, ZERO, (result & 0xFF) == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);
    set_flag(cpu, OVERFLOW, (~(a_value ^ value) & (a_value ^ result)) & 0x80);
    set_a(cpu, result & 0xFF);
}

void and(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t a_value = get_a(cpu);
    uint8_t result = a_value & value;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);
    set_a(cpu, result);
}

void asl(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t result = value << 1;

    set_flag(cpu, CARRY, value & 0x80);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    memory_write(get_mem(cpu), address, result);   
}
void bcc(struct cpu *cpu, uint16_t address) {
    if (get_flag(cpu, CARRY) == 0) {
        set_pc(cpu, address);
    }
}
void bcs(struct cpu *cpu, uint16_t address) {
    if (get_flag(cpu, CARRY) == 1) {
        set_pc(cpu, address);
    }
}

void beq(struct cpu *cpu, uint16_t address) {
    if (get_flag(cpu, ZERO) == 1) {
        set_pc(cpu, address);
    }
}

void bit(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t a_value = get_a(cpu);
    uint8_t result = a_value & value;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, value & (1 << 7));
    set_flag(cpu, OVERFLOW, value & (1 << 6));
}

void bmi(struct cpu *cpu, uint16_t address) {
    if (get_flag(cpu, NEGATIVE) == 1) {
        set_pc(cpu, address);
    }
}

void bne(struct cpu *cpu, uint16_t address) {
    if (get_flag(cpu, ZERO) == 0) {
        set_pc(cpu, address);
    }
}

void bpl(struct cpu *cpu, uint16_t address) {
    if (get_flag(cpu, NEGATIVE) == 0) {
        set_pc(cpu, address);
    }
}

void brk(struct cpu *cpu, uint16_t address) {
    (void) address;
    set_flag(cpu, BREAK, 1);
}

void bvc(struct cpu *cpu, uint16_t address) {
    if (get_flag(cpu, OVERFLOW) == 0) {
        set_pc(cpu, address);
    }
}

void bvs(struct cpu *cpu, uint16_t address) {
    if (get_flag(cpu, OVERFLOW) == 1) {
        set_pc(cpu, address);
    }
}

void clc(struct cpu *cpu, uint16_t address) {
    (void) address;
    set_flag(cpu, CARRY, 0);
}

void cld(struct cpu *cpu, uint16_t address) {
    (void) address;
    set_flag(cpu, DECIMAL, 0);
}

void cli(struct cpu *cpu, uint16_t address) {
    (void) address;
    set_flag(cpu, INTERRUPT, 0);
}

void clv(struct cpu *cpu, uint16_t address) {
    (void) address;
    set_flag(cpu, OVERFLOW, 0);
}

void cmp(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t a_value = get_a(cpu);
    uint8_t result = a_value - value;

    set_flag(cpu, CARRY, a_value >= value);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);
}

void cpx(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t x_value = get_x(cpu);
    uint8_t result = x_value - value;

    set_flag(cpu, CARRY, x_value >= value);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);
}

void cpy(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t y_value = get_y(cpu);
    uint8_t result = y_value - value;

    set_flag(cpu, CARRY, y_value >= value);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);
}

void dec(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t result = value - 1;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    memory_write(get_mem(cpu), address, result);
}

void dex(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t x_value = get_x(cpu);
    uint8_t result = x_value - 1;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    set_x(cpu, result);
}

void dey(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t y_value = get_y(cpu);
    uint8_t result = y_value - 1;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    set_y(cpu, result);
}

void eor(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t a_value = get_a(cpu);
    uint8_t result = a_value ^ value;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    set_a(cpu, result);
}

void inc(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t result = value + 1;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    memory_write(get_mem(cpu), address, result);
}

void inx(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t x_value = get_x(cpu);
    uint8_t result = x_value + 1;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    set_x(cpu, result);
}

void iny(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t y_value = get_y(cpu);
    uint8_t result = y_value + 1;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    set_y(cpu, result);
}

void jmp(struct cpu *cpu, uint16_t address) {
    set_pc(cpu, address);
}

void jsr(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint16_t pc = get_pc(cpu);
    uint8_t pc_high = (pc >> 8) & 0xFF;
    uint8_t pc_low = pc & 0xFF;

    push(cpu, pc_high);
    push(cpu, pc_low);

    set_pc(cpu, address);
}

void lda(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);

    set_flag(cpu, ZERO, value == 0);
    set_flag(cpu, NEGATIVE, value & 0x80);

    set_a(cpu, value);
}

void ldx(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);

    set_flag(cpu, ZERO, value == 0);
    set_flag(cpu, NEGATIVE, value & 0x80);

    set_x(cpu, value);
}

void ldy(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);

    set_flag(cpu, ZERO, value == 0);
    set_flag(cpu, NEGATIVE, value & 0x80);

    set_y(cpu, value);
}

void lsr(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t result = value >> 1;

    set_flag(cpu, CARRY, value & 0x01);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    memory_write(get_mem(cpu), address, result);
}

void nop(struct cpu *cpu, uint16_t address) {
    (void) address;
    (void) cpu;
    // do nothing
}

void ora(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t a_value = get_a(cpu);
    uint8_t result = a_value | value;

    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    set_a(cpu, result);
}

void pha(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t a_value = get_a(cpu);
    push(cpu, a_value);
}

void php(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t p_value = get_flags(cpu);
    push(cpu, p_value);
}

void pla(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t value = pull(cpu);
    set_a(cpu, value);
}

void plp(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t value = pull(cpu);
    set_flags(cpu, value);
}

void rol(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t result = (value << 1) | get_flag(cpu, CARRY);

    set_flag(cpu, CARRY, value & 0x80);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    memory_write(get_mem(cpu), address, result);
}

void ror(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t result = (value >> 1) | (get_flag(cpu, CARRY) << 7);

    set_flag(cpu, CARRY, value & 0x01);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);

    memory_write(get_mem(cpu), address, result);
}

void rti(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t p_value = pull(cpu);
    set_flags(cpu, p_value);

    uint8_t pc_low = pull(cpu);
    uint8_t pc_high = pull(cpu);
    uint16_t pc = (pc_high << 8) | pc_low;
    set_pc(cpu, pc);
}

void rts(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t pc_low = pull(cpu);
    uint8_t pc_high = pull(cpu);
    uint16_t pc = (pc_high << 8) | pc_low;
    set_pc(cpu, pc + 1);
}

void sbc(struct cpu *cpu, uint16_t address) {
    uint8_t value = memory_read(get_mem(cpu), address);
    uint8_t a_value = get_a(cpu);
    uint8_t carry = get_flag(cpu, CARRY);
    uint8_t result = a_value - value - (1 - carry);

    set_flag(cpu, CARRY, result <= a_value);
    set_flag(cpu, ZERO, result == 0);
    set_flag(cpu, NEGATIVE, result & 0x80);
    set_flag(cpu, OVERFLOW, ((a_value ^ result) & 0x80) && ((a_value ^ value) & 0x80));

    set_a(cpu, result);    
}

void sec(struct cpu *cpu, uint16_t address) {
    (void) address;
    set_flag(cpu, CARRY, 1);
}

void sed(struct cpu *cpu, uint16_t address) {
    (void) address;
    set_flag(cpu, DECIMAL, 1);
}

void sei(struct cpu *cpu, uint16_t address) {
    (void) address;
    set_flag(cpu, INTERRUPT, 1);
}

void sta(struct cpu *cpu, uint16_t address) {
    uint8_t a_value = get_a(cpu);
    memory_write(get_mem(cpu), address, a_value);
}

void stx(struct cpu *cpu, uint16_t address) {
    uint8_t x_value = get_x(cpu);
    memory_write(get_mem(cpu), address, x_value);
}

void sty(struct cpu *cpu, uint16_t address) {
    uint8_t y_value = get_y(cpu);
    memory_write(get_mem(cpu), address, y_value);
}

void tax(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t a_value = get_a(cpu);
    set_x(cpu, a_value);
}

void tay(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t a_value = get_a(cpu);
    set_y(cpu, a_value);
}

void tsx(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t sp_value = get_sp(cpu);
    set_x(cpu, sp_value);
}

void txa(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t x_value = get_x(cpu);
    set_a(cpu, x_value);
}

void txs(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t x_value = get_x(cpu);
    set_sp(cpu, x_value);
}

void tya(struct cpu *cpu, uint16_t address) {
    (void) address;
    uint8_t y_value = get_y(cpu);
    set_a(cpu, y_value);
}

struct instruction iset[ISET_SIZE] = {
//0xa9 | 0xa5 | 0xb5 | 0xad | 0xbd | 0xb9 | 0xa1 | 0xb1 lda
    [0xa9] = {
        .opcode = 0xa9,
        .name = "lda",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = lda
    },
    [0xa5] = {
        .opcode = 0xa5,
        .name = "lda",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = lda
    },
    [0xb5] = {
        .opcode = 0xb5,
        .name = "lda",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = lda
    },
    [0xad] = {
        .opcode = 0xad,
        .name = "lda",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = lda
    },
    [0xbd] = {
        .opcode = 0xbd,
        .name = "lda",
        .bytes = 3,
        .cycles = 4, //+1 if page crossed
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 1,
        .execute = lda
    },
    [0xb9] = {
        .opcode = 0xb9,
        .name = "lda",
        .bytes = 3,
        .cycles = 4, //+1 if page crossed
        .addr_mode = ABSOLUTE_Y,
        .cross_page_cycles = 1,
        .execute = lda
    },
    [0xa1] = {
        .opcode = 0xa1,
        .name = "lda",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = INDIRECT_X,
        .cross_page_cycles = 0,
        .execute = lda
    },
    [0xb1] = {
        .opcode = 0xb1,
        .name = "lda",
        .bytes = 2,
        .cycles = 5, //+1 if page crossed
        .addr_mode = INDIRECT_Y,
        .cross_page_cycles = 1,
        .execute = lda
    },

//0xAA tax
    [0xaa] = {
        .opcode = 0xaa,
        .name = "tax",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = tax
    },
//0xE8 inx
    [0xe8] = {
        .opcode = 0xe8,
        .name = "inx",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = inx
    },
//0x00 brk
    [0x00] = {
        .opcode = 0x00,
        .name = "brk",
        .bytes = 1,
        .cycles = 7,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = brk
    },
//0xD8 cld
    [0xd8] = {
        .opcode = 0xd8,
        .name = "cld",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = cld
    },
//0x58 cli
    [0x58] = {
        .opcode = 0x58,
        .name = "cli",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = cli
    },
//0xB8 clv
    [0xb8] = {
        .opcode = 0xb8,
        .name = "clv",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = clv
    },
//0x18 clc
    [0x18] = {
        .opcode = 0x18,
        .name = "clc",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = clc
    },
//0x38 sec
    [0x38] = {
        .opcode = 0x38,
        .name = "sec",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = sec
    },
//0x78 sei
    [0x78] = {
        .opcode = 0x78,
        .name = "sei",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = sei
    },
//0xf8 sed
    [0xf8] = {
        .opcode = 0xf8,
        .name = "sed",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = sed
    },
//0x48 pha
    [0x48] = {
        .opcode = 0x48,
        .name = "pha",
        .bytes = 1,
        .cycles = 3,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = pha
    },
//0x68 pla
    [0x68] = {
        .opcode = 0x68,
        .name = "pla",
        .bytes = 1,
        .cycles = 4,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = pla
    },
//0x08 php
    [0x08] = {
        .opcode = 0x08,
        .name = "php",
        .bytes = 1,
        .cycles = 3,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = php
    },
//0x28 plp
    [0x28] = {
        .opcode = 0x28,
        .name = "plp",
        .bytes = 1,
        .cycles = 4,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = plp
    },
//0x69 | 0x65 | 0x75 | 0x6d | 0x7d | 0x79 | 0x61 | 0x71 adc
    [0x69] = {
        .opcode = 0x69,
        .name = "adc",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = adc
    },
    [0x65] = {
        .opcode = 0x65,
        .name = "adc",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = adc
    },
    [0x75] = {
        .opcode = 0x75,
        .name = "adc",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = adc
    },
    [0x6d] = {
        .opcode = 0x6d,
        .name = "adc",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = adc
    },
    [0x7d] = {
        .opcode = 0x7d,
        .name = "adc",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 1,
        .execute = adc
    },
    [0x79] = {
        .opcode = 0x79,
        .name = "adc",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_Y,
        .cross_page_cycles = 1,
        .execute = adc
    },
    [0x61] = {
        .opcode = 0x61,
        .name = "adc",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = INDIRECT_X,
        .cross_page_cycles = 0,
        .execute = adc
    },
    [0x71] = {
        .opcode = 0x71,
        .name = "adc",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = INDIRECT_Y,
        .cross_page_cycles = 1,
        .execute = adc
    },
//0xe9 | 0xe5 | 0xf5 | 0xed | 0xfd | 0xf9 | 0xe1 | 0xf1 sbc
    [0xe9] = {
        .opcode = 0xe9,
        .name = "sbc",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = sbc
    },
    [0xe5] = {
        .opcode = 0xe5,
        .name = "sbc",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = sbc
    },
    [0xf5] = {
        .opcode = 0xf5,
        .name = "sbc",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = sbc
    },
    [0xed] = {
        .opcode = 0xed,
        .name = "sbc",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = sbc
    },
    [0xfd] = {
        .opcode = 0xfd,
        .name = "sbc",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 1,
        .execute = sbc
    },
    [0xf9] = {
        .opcode = 0xf9,
        .name = "sbc",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_Y,
        .cross_page_cycles = 1,
        .execute = sbc
    },
    [0xe1] = {
        .opcode = 0xe1,
        .name = "sbc",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = INDIRECT_X,
        .cross_page_cycles = 0,
        .execute = sbc
    },
    [0xf1] = {
        .opcode = 0xf1,
        .name = "sbc",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = INDIRECT_Y,
        .cross_page_cycles = 1,
        .execute = sbc
    },
//0x29 | 0x25 | 0x35 | 0x2d | 0x3d | 0x39 | 0x21 | 0x31 and
    [0x29] = {
        .opcode = 0x29,
        .name = "and",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = and
    },
    [0x25] = {
        .opcode = 0x25,
        .name = "and",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = and
    },
    [0x35] = {
        .opcode = 0x35,
        .name = "and",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = and
    },
    [0x2d] = {
        .opcode = 0x2d,
        .name = "and",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = and
    },
    [0x3d] = {
        .opcode = 0x3d,
        .name = "and",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 1,
        .execute = and
    },
    [0x39] = {
        .opcode = 0x39,
        .name = "and",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_Y,
        .cross_page_cycles = 1,
        .execute = and
    },
    [0x21] = {
        .opcode = 0x21,
        .name = "and",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = INDIRECT_X,
        .cross_page_cycles = 0,
        .execute = and
    },
    [0x31] = {
        .opcode = 0x31,
        .name = "and",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = INDIRECT_Y,
        .cross_page_cycles = 1,
        .execute = and
    },
//0x49 | 0x45 | 0x55 | 0x4d | 0x5d | 0x59 | 0x41 | 0x51 eor
    [0x49] = {
        .opcode = 0x49,
        .name = "eor",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = eor
    },
    [0x45] = {
        .opcode = 0x45,
        .name = "eor",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = eor
    },
    [0x55] = {
        .opcode = 0x55,
        .name = "eor",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = eor
    },
    [0x4d] = {
        .opcode = 0x4d,
        .name = "eor",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = eor
    },
    [0x5d] = {
        .opcode = 0x5d,
        .name = "eor",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 1,
        .execute = eor
    },
    [0x59] = {
        .opcode = 0x59,
        .name = "eor",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_Y,
        .cross_page_cycles = 1,
        .execute = eor
    },
    [0x41] = {
        .opcode = 0x41,
        .name = "eor",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = INDIRECT_X,
        .cross_page_cycles = 0,
        .execute = eor
    },
    [0x51] = {
        .opcode = 0x51,
        .name = "eor",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = INDIRECT_Y,
        .cross_page_cycles = 1,
        .execute = eor
    },
//0x09 | 0x05 | 0x15 | 0x0d | 0x1d | 0x19 | 0x01 | 0x11 ora
    [0x09] = {
        .opcode = 0x09,
        .name = "ora",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = ora
    },
    [0x05] = {
        .opcode = 0x05,
        .name = "ora",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = ora
    },
    [0x15] = {
        .opcode = 0x15,
        .name = "ora",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = ora
    },
    [0x0d] = {
        .opcode = 0x0d,
        .name = "ora",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = ora
    },
    [0x1d] = {
        .opcode = 0x1d,
        .name = "ora",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 1,
        .execute = ora
    },
    [0x19] = {
        .opcode = 0x19,
        .name = "ora",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_Y,
        .cross_page_cycles = 1,
        .execute = ora
    },
    [0x01] = {
        .opcode = 0x01,
        .name = "ora",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = INDIRECT_X,
        .cross_page_cycles = 0,
        .execute = ora
    },
    [0x11] = {
        .opcode = 0x11,
        .name = "ora",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = INDIRECT_Y,
        .cross_page_cycles = 1,
        .execute = ora
    },
//0x4A lsr acc
    [0x4a] = {
        .opcode = 0x4a,
        .name = "lsr",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = ACCUMULATOR,
        .cross_page_cycles = 0,
        .execute = lsr
    },
//0x46 | 0x56 | 0x4e | 0x5e lsr
    [0x46] = {
        .opcode = 0x46,
        .name = "lsr",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = lsr
    },
    [0x56] = {
        .opcode = 0x56,
        .name = "lsr",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = lsr
    },
    [0x4e] = {
        .opcode = 0x4e,
        .name = "lsr",
        .bytes = 3,
        .cycles = 6,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = lsr
    },
    [0x5e] = {
        .opcode = 0x5e,
        .name = "lsr",
        .bytes = 3,
        .cycles = 7,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 0,
        .execute = lsr
    },
//0x0a asl acc
    [0x0a] = {
        .opcode = 0x0a,
        .name = "asl",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = ACCUMULATOR,
        .cross_page_cycles = 0,
        .execute = asl
    },
//0x06 | 0x16 | 0x0e | 0x1e asl
    [0x06] = {
        .opcode = 0x06,
        .name = "asl",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = asl
    },
    [0x16] = {
        .opcode = 0x16,
        .name = "asl",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = asl
    },
    [0x0e] = {
        .opcode = 0x0e,
        .name = "asl",
        .bytes = 3,
        .cycles = 6,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = asl
    },
    [0x1e] = {
        .opcode = 0x1e,
        .name = "asl",
        .bytes = 3,
        .cycles = 7,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 0,
        .execute = asl
    },
//0x2a rol acc
    [0x2a] = {
        .opcode = 0x2a,
        .name = "rol",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = ACCUMULATOR,
        .cross_page_cycles = 0,
        .execute = rol
    },
//0x26 | 0x36 | 0x2e | 0x3e rol
    [0x26] = {
        .opcode = 0x26,
        .name = "rol",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = rol
    },
    [0x36] = {
        .opcode = 0x36,
        .name = "rol",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = rol
    },
    [0x2e] = {
        .opcode = 0x2e,
        .name = "rol",
        .bytes = 3,
        .cycles = 6,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = rol
    },
    [0x3e] = {
        .opcode = 0x3e,
        .name = "rol",
        .bytes = 3,
        .cycles = 7,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 0,
        .execute = rol
    },
//0x6a ror acc
    [0x6a] = {
        .opcode = 0x6a,
        .name = "ror",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = ACCUMULATOR,
        .cross_page_cycles = 0,
        .execute = ror
    },
//0x66 | 0x76 | 0x6e | 0x7e ror
    [0x66] = {
        .opcode = 0x66,
        .name = "ror",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = ror
    },
    [0x76] = {
        .opcode = 0x76,
        .name = "ror",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = ror
    },
    [0x6e] = {
        .opcode = 0x6e,
        .name = "ror",
        .bytes = 3,
        .cycles = 6,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = ror
    },
    [0x7e] = {
        .opcode = 0x7e,
        .name = "ror",
        .bytes = 3,
        .cycles = 7,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 0,
        .execute = ror
    },
//0xe6 | 0xf6 | 0xee | 0xfe inc
    [0xe6] = {
        .opcode = 0xe6,
        .name = "inc",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = inc
    },
    [0xf6] = {
        .opcode = 0xf6,
        .name = "inc",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = inc
    },
    [0xee] = {
        .opcode = 0xee,
        .name = "inc",
        .bytes = 3,
        .cycles = 6,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = inc
    },
    [0xfe] = {
        .opcode = 0xfe,
        .name = "inc",
        .bytes = 3,
        .cycles = 7,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 0,
        .execute = inc
    },
//0xc8 iny
    [0xc8] = {
        .opcode = 0xc8,
        .name = "iny",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = iny
    },
//0xc6 | 0xd6 | 0xce | 0xde dec
    [0xc6] = {
        .opcode = 0xc6,
        .name = "dec",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = dec
    },
    [0xd6] = {
        .opcode = 0xd6,
        .name = "dec",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = dec
    },
    [0xce] = {
        .opcode = 0xce,
        .name = "dec",
        .bytes = 3,
        .cycles = 6,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = dec
    },
    [0xde] = {
        .opcode = 0xde,
        .name = "dec",
        .bytes = 3,
        .cycles = 7,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 0,
        .execute = dec
    },
//0xca dex
    [0xca] = {
        .opcode = 0xca,
        .name = "dex",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = dex
    },
//0x88 dey
    [0x88] = {
        .opcode = 0x88,
        .name = "dey",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = dey
    },
//0xc9 | 0xc5 | 0xd5 | 0xcd | 0xdd | 0xd9 | 0xc1 | 0xd1 cmp
    [0xc9] = {
        .opcode = 0xc9,
        .name = "cmp",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = cmp
    },
    [0xc5] = {
        .opcode = 0xc5,
        .name = "cmp",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = cmp
    },
    [0xd5] = {
        .opcode = 0xd5,
        .name = "cmp",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = cmp
    },
    [0xcd] = {
        .opcode = 0xcd,
        .name = "cmp",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = cmp
    },
    [0xdd] = {
        .opcode = 0xdd,
        .name = "cmp",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 1,
        .execute = cmp
    },
    [0xd9] = {
        .opcode = 0xd9,
        .name = "cmp",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_Y,
        .cross_page_cycles = 1,
        .execute = cmp
    },
    [0xc1] = {
        .opcode = 0xc1,
        .name = "cmp",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = INDIRECT_X,
        .cross_page_cycles = 0,
        .execute = cmp
    },
    [0xd1] = {
        .opcode = 0xd1,
        .name = "cmp",
        .bytes = 2,
        .cycles = 5,
        .addr_mode = INDIRECT_Y,
        .cross_page_cycles = 1,
        .execute = cmp
    },
//0xc0 | 0xc4 | 0xcc cpy
    [0xc0] = {
        .opcode = 0xc0,
        .name = "cpy",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = cpy
    },
    [0xc4] = {
        .opcode = 0xc4,
        .name = "cpy",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = cpy
    },
    [0xcc] = {
        .opcode = 0xcc,
        .name = "cpy",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = cpy
    },
//0xe0 | 0xe4 | 0xec cpx
    [0xe0] = {
        .opcode = 0xe0,
        .name = "cpx",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = cpx
    },
    [0xe4] = {
        .opcode = 0xe4,
        .name = "cpx",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = cpx
    },
    [0xec] = {
        .opcode = 0xec,
        .name = "cpx",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = cpx
    },
//0x4c jmp abs
    [0x4c] = {
        .opcode = 0x4c,
        .name = "jmp",
        .bytes = 3,
        .cycles = 3,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = jmp
    },
//0x6c jmp ind
    [0x6c] = {
        .opcode = 0x6c,
        .name = "jmp",
        .bytes = 3,
        .cycles = 5,
        .addr_mode = INDIRECT,
        .cross_page_cycles = 0,
        .execute = jmp
    },
//0x20 jsr
    [0x20] = {
        .opcode = 0x20,
        .name = "jsr",
        .bytes = 3,
        .cycles = 6,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = jsr
    },
//0x60 rts
    [0x60] = {
        .opcode = 0x60,
        .name = "rts",
        .bytes = 1,
        .cycles = 6,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = rts
    },
//0x40 rti
    [0x40] = {
        .opcode = 0x40,
        .name = "rti",
        .bytes = 1,
        .cycles = 6,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = rti
    },
//0xd0 bne
    [0xd0] = {
        .opcode = 0xd0,
        .name = "bne",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = RELATIVE,
        .cross_page_cycles = 1,
        .execute = bne
    },
//0x70 bvs
    [0x70] = {
        .opcode = 0x70,
        .name = "bvs",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = RELATIVE,
        .cross_page_cycles = 1,
        .execute = bvs
    },
//0x50 bvc
    [0x50] = {
        .opcode = 0x50,
        .name = "bvc",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = RELATIVE,
        .cross_page_cycles = 1,
        .execute = bvc
    },
//0x10 bpl
    [0x10] = {
        .opcode = 0x10,
        .name = "bpl",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = RELATIVE,
        .cross_page_cycles = 1,
        .execute = bpl
    },
//0x30 bmi
    [0x30] = {
        .opcode = 0x30,
        .name = "bmi",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = RELATIVE,
        .cross_page_cycles = 1,
        .execute = bmi
    },
//0xf0 beq
    [0xf0] = {
        .opcode = 0xf0,
        .name = "beq",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = RELATIVE,
        .cross_page_cycles = 1,
        .execute = beq
    },
//0xb0 bcs
    [0xb0] = {
        .opcode = 0xb0,
        .name = "bcs",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = RELATIVE,
        .cross_page_cycles = 1,
        .execute = bcs
    },
//0x90 bcc
    [0x90] = {
        .opcode = 0x90,
        .name = "bcc",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = RELATIVE,
        .cross_page_cycles = 1,
        .execute = bcc
    },
//0x24 | 0x2c bit
    [0x24] = {
        .opcode = 0x24,
        .name = "bit",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = bit
    },
    [0x2c] = {
        .opcode = 0x2c,
        .name = "bit",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = bit
    },
//0x85 | 0x95 | 0x8d | 0x9d | 0x99 | 0x81 | 0x91 sta
    [0x85] = {
        .opcode = 0x85,
        .name = "sta",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = sta
    },
    [0x95] = {
        .opcode = 0x95,
        .name = "sta",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = sta
    },
    [0x8d] = {
        .opcode = 0x8d,
        .name = "sta",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = sta
    },
    [0x9d] = {
        .opcode = 0x9d,
        .name = "sta",
        .bytes = 3,
        .cycles = 5,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 0,
        .execute = sta
    },
    [0x99] = {
        .opcode = 0x99,
        .name = "sta",
        .bytes = 3,
        .cycles = 5,
        .addr_mode = ABSOLUTE_Y,
        .cross_page_cycles = 0,
        .execute = sta
    },
    [0x81] = {
        .opcode = 0x81,
        .name = "sta",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = INDIRECT_X,
        .cross_page_cycles = 0,
        .execute = sta
    },
    [0x91] = {
        .opcode = 0x91,
        .name = "sta",
        .bytes = 2,
        .cycles = 6,
        .addr_mode = INDIRECT_Y,
        .cross_page_cycles = 0,
        .execute = sta
    },
//0x86 | 0x96 | 0x8e stx
    [0x86] = {
        .opcode = 0x86,
        .name = "stx",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = stx
    },
    [0x96] = {
        .opcode = 0x96,
        .name = "stx",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_Y,
        .cross_page_cycles = 0,
        .execute = stx
    },
    [0x8e] = {
        .opcode = 0x8e,
        .name = "stx",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = stx
    },
//0x84 | 0x94 | 0x8c sty
    [0x84] = {
        .opcode = 0x84,
        .name = "sty",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = sty
    },
    [0x94] = {
        .opcode = 0x94,
        .name = "sty",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = sty
    },
    [0x8c] = {
        .opcode = 0x8c,
        .name = "sty",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = sty
    },
//0xa2 | 0xa6 | 0xb6 | 0xae | 0xbe ldx
    [0xa2] = {
        .opcode = 0xa2,
        .name = "ldx",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = ldx
    },
    [0xa6] = {
        .opcode = 0xa6,
        .name = "ldx",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = ldx
    },
    [0xb6] = {
        .opcode = 0xb6,
        .name = "ldx",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_Y,
        .cross_page_cycles = 0,
        .execute = ldx
    },
    [0xae] = {
        .opcode = 0xae,
        .name = "ldx",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = ldx
    },
    [0xbe] = {
        .opcode = 0xbe,
        .name = "ldx",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_Y,
        .cross_page_cycles = 0,
        .execute = ldx
    },
//0xa0 | 0xa4 | 0xb4 | 0xac | 0xbc ldy
    [0xa0] = {
        .opcode = 0xa0,
        .name = "ldy",
        .bytes = 2,
        .cycles = 2,
        .addr_mode = IMMEDIATE,
        .cross_page_cycles = 0,
        .execute = ldy
    },
    [0xa4] = {
        .opcode = 0xa4,
        .name = "ldy",
        .bytes = 2,
        .cycles = 3,
        .addr_mode = ZERO_PAGE,
        .cross_page_cycles = 0,
        .execute = ldy
    },
    [0xb4] = {
        .opcode = 0xb4,
        .name = "ldy",
        .bytes = 2,
        .cycles = 4,
        .addr_mode = ZERO_PAGE_X,
        .cross_page_cycles = 0,
        .execute = ldy
    },
    [0xac] = {
        .opcode = 0xac,
        .name = "ldy",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE,
        .cross_page_cycles = 0,
        .execute = ldy
    },
    [0xbc] = {
        .opcode = 0xbc,
        .name = "ldy",
        .bytes = 3,
        .cycles = 4,
        .addr_mode = ABSOLUTE_X,
        .cross_page_cycles = 0,
        .execute = ldy
    },
//0xea nop
    [0xea] = {
        .opcode = 0xea,
        .name = "nop",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = nop
    },
//0xa8 tay
    [0xa8] = {
        .opcode = 0xa8,
        .name = "tay",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = tay
    },
//0xba tsx
    [0xba] = {
        .opcode = 0xba,
        .name = "tsx",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = tsx
    },
//0x8a txa
    [0x8a] = {
        .opcode = 0x8a,
        .name = "txa",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = txa
    },
//0x9a txs
    [0x9a] = {
        .opcode = 0x9a,
        .name = "txs",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = txs
    },
//0x98 tya
    [0x98] = {
        .opcode = 0x98,
        .name = "tya",
        .bytes = 1,
        .cycles = 2,
        .addr_mode = IMPLIED,
        .cross_page_cycles = 0,
        .execute = tya
    }
};

struct instruction * get_instruction(uint8_t opcode) {
    struct instruction *instruction = &iset[opcode];
    if (instruction->opcode != opcode) {
        printf("Invalid opcode: %02x\n", opcode);
        exit(1);
    }
    return &iset[opcode];
}

void dissasemble(uint8_t *memory, uint16_t address, uint32_t length) {
    uint16_t pc = address;
    while (pc < address + length) {
        uint8_t opcode = memory[pc];
        struct instruction *instruction = &iset[opcode];
        printf("[%04x] %02x %s", pc, opcode, instruction->name);
        for (int i = 1; i < instruction->bytes; i++) {
            printf(" %02x", memory[pc + i]);
        }
        printf("\n");
        pc += instruction->bytes;
    }
}