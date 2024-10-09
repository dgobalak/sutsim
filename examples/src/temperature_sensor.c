#include "temperature_sensor.h"
#include "sutsim.h"

#include <stdint.h>
#include <stdbool.h>

#define DEVICE_TAG "temperature_sensor"
#define TEMPERATURE_CELSIUS_TAG "temperature_sensor.temperature"

typedef struct {
    float temperature;
} sensor_data_S;

static sensor_data_S sensor_data = {0.0f};

temperature_sensor_status_E temperature_sensor_init(void) {
    sutsim_add_tag(TEMPERATURE_CELSIUS_TAG, &sensor_data.temperature, sizeof(float), SUTSIM_FLOAT);
    return TEMPERATURE_SENSOR_SUCCESS;
}

temperature_sensor_status_E temperature_sensor_readCelsius(float* temperature) {
    sutsim_read(TEMPERATURE_CELSIUS_TAG, temperature, sizeof(float));
    return TEMPERATURE_SENSOR_SUCCESS;
}
