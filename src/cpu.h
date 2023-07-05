#ifndef _CPU_H
#define _CPU_H
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

struct registers {
    uint16_t pc;
    uint8_t sp;
    uint8_t a;
    uint8_t x;
    uint8_t y;
    struct sr sr;
} __attribute__((packed));


#endif