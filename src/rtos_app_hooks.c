#include "temperature_sensor.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <stdio.h>
#include <stdint.h>

/* DEFINES */
#define QUEUE_LENGTH 10
#define QUEUE_ITEM_SIZE sizeof(float)

/* TYPEDEFS */
typedef struct {
    QueueHandle_t queue;
    StaticQueue_t queueBuffer;
    uint8_t queueStorageArea[QUEUE_LENGTH * QUEUE_ITEM_SIZE];
} rtos_app_data_S;

/* PRIVATE VARIABLES */
static rtos_app_data_S rtos_app_data = {0};

/* PUBLIC FUNCTIONS */
void rtos_app_init(void) {
    rtos_app_data.queue = xQueueCreateStatic(QUEUE_LENGTH, QUEUE_ITEM_SIZE, rtos_app_data.queueStorageArea, &rtos_app_data.queueBuffer);
    (void)temperature_sensor_init();
}

void taskFunction_1kHz(void) {
    float t = 0.0f;
    if (temperature_sensor_readCelsius(&t) == TEMPERATURE_SENSOR_SUCCESS) {
        (void)xQueueSend(rtos_app_data.queue, &t, 0);
    }
}

void taskFunction_100Hz(void) {
    float t = 0.0f;
    (void)xQueueReceive(rtos_app_data.queue, &t, 0);
    printf("Firmware: Current temperature is %.2f°C\n", t);
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
