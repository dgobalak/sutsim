#include "sutsim.h"
#include "task_config.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"

extern void app_temperature_init(void);
extern void pwm_init(void);
extern void heater_init(void);

void sut_init_hook(void) {
    pwm_init();
    heater_init();
    app_temperature_init();
}

void sut_tick_hook(void) {
    // Assume tick rate is 1kHz
    static uint32_t tickCounter = 0;
    static bool     initialized  = false;

    if (!initialized) {
        task_executeAllInit();
        initialized = true;
    }

    task_executeAll(tickCounter);

    tickCounter = (tickCounter + 1) % 1000;
}

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    configSTACK_DEPTH_TYPE * puxIdleTaskStackSize )
{
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    *ppxIdleTaskTCBBuffer = &( xIdleTaskTCB );
    *ppxIdleTaskStackBuffer = &( uxIdleTaskStack[ 0 ] );
    *puxIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
