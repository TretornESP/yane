#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define RAM_START       0x0000
#define RAM_END         0x1FFF

#define IO_START        0x2000
#define IO_END          0x401F

#define EXP_ROM_START   0x4020
#define EXP_ROM_END     0x5FFF

#define SAVE_RAM_START   0x6000
#define SAVE_RAM_END     0x7FFF

#define PRG_ROM_START   0x8000
#define PRG_ROM_END     0xFFFF

#define RAM_SIZE        (RAM_END - RAM_START + 1)
#define IO_SIZE         (IO_END - IO_START + 1)
#define EXP_ROM_SIZE    (EXP_ROM_END - EXP_ROM_START + 1)
#define SAVE_RAM_SIZE   (SAVE_RAM_END - SAVE_RAM_START + 1)
#define PRG_ROM_SIZE    (PRG_ROM_END - PRG_ROM_START + 1)

#define MEMORY_SIZE     (RAM_SIZE + IO_SIZE + EXP_ROM_SIZE + SAVE_RAM_SIZE + PRG_ROM_SIZE)

struct memory {
    uint8_t ram[RAM_SIZE];
    uint8_t io[IO_SIZE];
    uint8_t exp_rom[EXP_ROM_SIZE];
    uint8_t save_ram[SAVE_RAM_SIZE];
    uint8_t prg_rom[PRG_ROM_SIZE];
} __attribute__((packed));

union memory_union {
    struct memory mem;
    uint8_t raw[MEMORY_SIZE];
};

void memory_init(union memory_union* memory);
void memory_reset(union memory_union* memory);
void memory_set_startup_vector(union memory_union* memory, uint16_t startup_vector);
void memory_set_at(union memory_union* memory, uint16_t addr, uint8_t *data, uint16_t size);
void memory_set_prg_rom(union memory_union* memory, uint8_t* rom, uint16_t rom_size);
uint8_t memory_read(union memory_union* memory, uint16_t addr);
uint8_t memory_read_silent(union memory_union* memory, uint16_t addr);
void memory_write(union memory_union* memory, uint16_t addr, uint8_t data);
void memory_write_silent(union memory_union* memory, uint16_t addr, uint8_t data);
void memory_write_word(union memory_union* memory, uint16_t addr, uint16_t data);
void memory_write_word_silent(union memory_union* memory, uint16_t addr, uint16_t data);
uint16_t memory_read_word(union memory_union* memory, uint16_t addr);
uint16_t memory_read_word_silent(union memory_union* memory, uint16_t addr);
uint8_t memory_read_relative(union memory_union* memory, uint16_t addr, uint8_t offset);
void memory_write_relative(union memory_union* memory, uint16_t addr, uint8_t offset, uint8_t data);

#endif