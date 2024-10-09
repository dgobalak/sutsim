#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    TEMPERATURE_SENSOR_SUCCESS = 0,         // Operation succeeded
} temperature_sensor_status_E;

/**
 * @brief Initialize the temperature sensor
 * 
 * @return temperature_sensor_status_E The status of the operation
 */
temperature_sensor_status_E temperature_sensor_init(void);

/**
 * @brief Read the temperature in Celsius from the sensor
 * 
 * @param temperature The temperature in Celsius
 * @return temperature_sensor_status_E The status of the operation
 */
temperature_sensor_status_E temperature_sensor_readCelsius(float* temperature);
