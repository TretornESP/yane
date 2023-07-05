#include <stdint.h>
#include "controller.h"

struct io_struct {
    uint8_t *screen;
    uint8_t *controller;
    uint8_t *random;
};

void * io_loop(void *data);