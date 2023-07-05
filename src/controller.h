#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <stdint.h>

#define CTRL_UP     0x01
#define CTRL_DOWN   0x02
#define CTRL_LEFT   0x04
#define CTRL_RIGHT  0x08
#define CTRL_A      0x10
#define CTRL_B      0x20
#define CTRL_SELECT 0x40
#define CTRL_START  0x80

struct controller {
    uint8_t a:1;
    uint8_t b:1;
    uint8_t select:1;
    uint8_t start:1;
    uint8_t up:1;
    uint8_t down:1;
    uint8_t left:1;
    uint8_t right:1;
} __attribute__((packed));

union controller_union {
    struct controller controller;
    uint8_t controller_byte;
};

void controller_init(struct controller *controller);
void controller_up(struct controller *controller);
void controller_down(struct controller *controller);
void controller_left(struct controller *controller);
void controller_right(struct controller *controller);
void controller_a(struct controller *controller);
void controller_b(struct controller *controller);
void controller_select(struct controller *controller);
void controller_start(struct controller *controller);

void controller_up_release(struct controller *controller);
void controller_down_release(struct controller *controller);
void controller_left_release(struct controller *controller);
void controller_right_release(struct controller *controller);
void controller_a_release(struct controller *controller);
void controller_b_release(struct controller *controller);
void controller_select_release(struct controller *controller);
void controller_start_release(struct controller *controller);

#endif