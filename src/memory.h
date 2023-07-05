#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define RAM_START       0x0000
#define RAM_END         0x1FFF

#define IO_START        0x2000
#define IO_END          0x401F

#define EXP_ROM_START   0x4020
#define EXP_ROM_END     0x5FFF

#define PRG_ROM_START   0x6000
#define PRG_ROM_END     0x7FFF

#define PRG_RAM_START   0x8000
#define PRG_RAM_END     0xFFFF

#define RAM_SIZE        0x2000
#define IO_SIZE         0x2020
#define EXP_ROM_SIZE    0x1980
#define SAVE_RAM_SIZE   0x2000
#define PRG_RAM_SIZE    0x2000

#define MEMORY_SIZE     (RAM_SIZE + IO_SIZE + EXP_ROM_SIZE + SAVE_RAM_SIZE + PRG_RAM_SIZE)

struct memory {
    uint8_t ram[RAM_SIZE];
    uint8_t io[IO_SIZE];
    uint8_t exp_rom[EXP_ROM_SIZE];
    uint8_t save_ram[SAVE_RAM_SIZE];
    uint8_t prg_ram[PRG_RAM_SIZE];
} __attribute__((packed));

union memory_union {
    struct memory mem;
    uint8_t raw[MEMORY_SIZE];
};

extern union memory_union memory;

void memory_init();
void memory_reset();
uint8_t memory_read(uint16_t addr);
void memory_write(uint16_t addr, uint8_t data);
uint8_t memory_read_relative(uint16_t addr, uint8_t offset);
void memory_write_relative(uint16_t addr, uint8_t offset, uint8_t data);

#endif