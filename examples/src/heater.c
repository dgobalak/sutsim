#include "heater.h"
#include "pwm.h"

#define HEATER_ON_PWM_FREQ  1000
#define HEATER_OFF_PWM_FREQ 0

void heater_init(void) {
    heater_disable();
}

void heater_enable(void) {
    pwm_set_freq(HEATER_ON_PWM_FREQ);
}

void heater_disable(void) {
    pwm_set_freq(HEATER_OFF_PWM_FREQ);
}