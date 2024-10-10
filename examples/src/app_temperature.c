#include "temperature_sensor.h"

#include "FreeRTOS.h"
#include "queue.h"

#include <stdio.h>
#include <stdint.h>

/* DEFINES */
#define APP_TEMPERATURES_QUEUE_LENGTH    10
#define APP_TEMPERATURES_QUEUE_ITEM_SIZE sizeof(float)

/* TYPEDEFS */
typedef struct {
    QueueHandle_t temperature_queue;
    StaticQueue_t temperature_queueBuffer;
    uint8_t       temperature_queueStorageArea[APP_TEMPERATURES_QUEUE_LENGTH * APP_TEMPERATURES_QUEUE_ITEM_SIZE];
} app_temperatures_S;

/* PRIVATE VARIABLES */
static app_temperatures_S app_temperatures = {0};

/* PUBLIC FUNCTIONS */
// Init function to be called before tasks are created
void app_temperature_init(void) {
    app_temperatures.temperature_queue = xQueueCreateStatic(APP_TEMPERATURES_QUEUE_LENGTH, APP_TEMPERATURES_QUEUE_ITEM_SIZE, app_temperatures.temperature_queueStorageArea, &app_temperatures.temperature_queueBuffer);
}

// Temperature reading task (periodic)
void taskFunction_readTemperature_init_100Hz(void) {
    (void)temperature_sensor_init();
}

void taskFunction_readTemperature_run_100Hz(void) {
    float t = 0.0f;
    if (temperature_sensor_readCelsius(&t) == TEMPERATURE_SENSOR_SUCCESS) {
        (void)xQueueSend(app_temperatures.temperature_queue, &t, 0);
    }
}

// Temperature processing task (event-driven)
void taskFunction_processTemperature_eventDriven(void) {
    float t = 0.0f;

    // Note: Non-zero block time does not work in sim
    if (xQueueReceive(app_temperatures.temperature_queue, &t, 0U) == pdTRUE) {
        printf("Firmware: Current temperature is %.2f°C\n", t);
    }
}
