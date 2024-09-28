#include "sut_firmware.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void sut_init_hook() {
    printf("Firmware initialized.\n");
}

void sut_tick_hook() {
    float temperature = 0.0f;
    sut_get_data("temperature_sensor.temperature", &temperature, sizeof(float));
    printf("Firmware: Current temperature is %.2f°C\n", temperature);
}
