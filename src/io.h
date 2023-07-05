#include <stdint.h>

void print_pixel(uint8_t x, uint8_t y, uint8_t color);
void read_controller(struct controller_state *state);
void play_sound(uint8_t freq);