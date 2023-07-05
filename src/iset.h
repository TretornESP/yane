#ifndef _ISET_H
#define _ISET_H
#include "cpu.h"

#define ADDR_INMEDITE       0x01
#define ADDR_ZERO_PAGE      0x02
#define ADDR_ZERO_PAGE_X    0x03
#define ADDR_ZERO_PAGE_Y    0x04
#define ADDR_ABSOLUTE       0x05
#define ADDR_ABSOLUTE_X     0x06
#define ADDR_ABSOLUTE_Y     0x07
#define ADDR_INDIRECT_X     0x08
#define ADDR_INDIRECT_Y     0x09
#define ADDR_NONE           0x0A

#define ISET_SIZE           256

struct instruction {
    uint8_t opcode;
    char mnemonic[4];
    uint8_t bytes;
    uint8_t cycles;
    uint8_t addressing;
};

extern struct instruction iset[ISET_SIZE];

void init_iset();
#endif