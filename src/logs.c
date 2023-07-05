#include "logs.h"
#include <stdio.h>

void dbg(char *function, char *message, ...) {
    va_list args;
    va_start(args, message);
    printf("[LOG] %s: ", function);
    vprintf(message, args);
    printf("\n");
    va_end(args);
}