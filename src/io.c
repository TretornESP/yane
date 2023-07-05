#include "io.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define SCREEN_SIZE 1024
#define SCREEN_WIDTH 32
#define FIFO "/tmp/nesfifo"

void print_screen(uint8_t *screen) {
    int ignored = system("clear");
    (void)ignored;

    for (uint16_t y = 0; y < SCREEN_SIZE; y++) {
        switch (screen[y]) {
            case 0:
                printf(" ");
                break;
            case 4:
                printf("@");
                break;
            case 3:
                printf("X");
                break;
            default:
                printf(" ");
                break;
        }
        if (y % SCREEN_WIDTH == 0)
            printf("\n");
    }
}

void read_fifo(uint8_t *ctrl, int fd) {

    uint8_t data;
    if (read(fd, &data, 1) == 0) {
        return;
    }

    ctrl[0] = data;
}

void generate_random(uint8_t *random) {
    random[0] = rand() % 256;
}

void play_sound(uint8_t freq) {
    (void)freq;
}

void * io_loop(void * data) {
    struct io_struct * io = (struct io_struct *)data;
    
    uint8_t *ctrl = io->controller;
    uint8_t * screen = io->screen;
    uint8_t * random = io->random;

    mkfifo(FIFO, 0666);
    int fd = open(FIFO, O_RDONLY);

    while (1) {
        read_fifo(ctrl, fd);
        print_screen(screen);
        generate_random(random);
        usleep(1000000 / 60);
    }
}