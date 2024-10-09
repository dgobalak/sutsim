#include "sutsim.h"
#include "temperature_sensor.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Hooks defined by application
extern void rtos_app_init(void);
extern void taskFunction_1kHz(void);
extern void taskFunction_100Hz(void);

void sut_init_hook(void) {
    rtos_app_init();
}

void sut_tick_hook(void) {
    // Assume tick rate is 1kHz

    static uint32_t tickCounter = 0;

    if (tickCounter % 1 == 0) {
        taskFunction_1kHz();
    }

    if (tickCounter % 10 == 0) {
        taskFunction_100Hz();
    }

    tickCounter = (tickCounter + 1) % 1000;
}
