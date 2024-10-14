#include "pwm.h"
#include "sutsim.h"

#include <stdint.h>

#define PWM_DEVICE_TAG  "pwm"
#define PWM_CH1_TAG     "pwm.freq.ch1"

typedef struct {
    uint32_t ch1_freq;
} pwm_S;

static pwm_S pwm = {0};

void pwm_init(void) {
    sutsim_add_tag(PWM_CH1_TAG, &pwm.ch1_freq, sizeof(pwm.ch1_freq), SUTSIM_UINT32, NULL, false);
}

void pwm_set_freq(uint32_t value) {
    sutsim_write(PWM_CH1_TAG, &value, sizeof(value));
}
