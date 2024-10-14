#include "temperature_sensor.h"
#include "sutsim.h"

#include <stdint.h>
#include <stdbool.h>

#define DEVICE_TAG              "temperature_sensor"
#define TEMPERATURE_CELSIUS_TAG "temperature_sensor.temperature"
#define TEMPERATURE_STATUS_TAG  "temperature_sensor.status"

typedef struct {
    float    temperature;
    uint32_t status;
} sensor_data_S;

static sensor_data_S sensor_data = {0.0f};

temperature_sensor_status_E temperature_sensor_init(void) {
    sutsim_add_tag(TEMPERATURE_CELSIUS_TAG, &sensor_data.temperature, sizeof(float), SUTSIM_FLOAT, NULL, false);
    sutsim_add_tag(TEMPERATURE_STATUS_TAG, &sensor_data.status, sizeof(uint32_t), SUTSIM_UINT32, NULL, false);
    return TEMPERATURE_SENSOR_SUCCESS;
}

temperature_sensor_status_E temperature_sensor_readCelsius(float* temperature) {
    *temperature = sensor_data.temperature;
    return TEMPERATURE_SENSOR_SUCCESS;
}

uint8_t temperature_sensor_readStatus(void) {
    return (uint8_t)(sensor_data.status & 0xFF);
}
