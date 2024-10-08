#include "sutsim.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#define QUEUE_LENGTH 10
#define ITEM_SIZE sizeof(float)

QueueHandle_t xQueue = NULL;
StaticQueue_t xQueueBuffer;
uint8_t ucQueueStorageArea[QUEUE_LENGTH * ITEM_SIZE] = {0};

static float temperature = 0.0f;

static void taskFunction_1kHz(void) {
    xQueueSend(xQueue, &temperature, 0U);
}

static void taskFunction_100Hz(void) {
    float t = 0.0f;
    xQueueReceive(xQueue, &t, 0U);
    printf("Firmware: Current temperature is %.2f°C\n", t);
}

void sut_init_hook(void) {
    sutsim_add_tag("temperature_sensor.temperature", &temperature, sizeof(float), SUTSIM_FLOAT);

    printf("Firmware initialized.\n");
    xQueue = xQueueCreateStatic(QUEUE_LENGTH, ITEM_SIZE, ucQueueStorageArea, &xQueueBuffer);
}

void sut_tick_hook(void) {
    static uint32_t tickCounter = 0;

    taskFunction_1kHz();

    if (tickCounter % 10 == 0) {
        taskFunction_100Hz();
    }

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
