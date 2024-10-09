#include "sutsim.h"
#include "task_config.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Hooks defined by application
extern void rtos_app_init(void);

void sut_init_hook(void) {
    rtos_app_init();
}

void sut_tick_hook(void) {
    // Assume tick rate is 1kHz
    static uint32_t tickCounter = 0;

    task_tryRunningAll(tickCounter);

    tickCounter = (tickCounter + 1) % 1000;
}
