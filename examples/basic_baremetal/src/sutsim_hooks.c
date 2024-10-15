#include "sutsim.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void sut_init_hook(void) {
    printf("SUT initialized\n");
}

void sut_tick_hook(void) {
    // Assume tick rate is 1kHz
    static uint32_t tickCounter = 0;

    printf("Tick count: %d\n", tickCounter);

    tickCounter = (tickCounter + 1) % 1000;
}
