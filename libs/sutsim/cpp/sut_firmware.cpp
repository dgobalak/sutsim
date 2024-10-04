#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "SutState.hpp"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    bool initialized;
    SutState stateData;
} sut_data_S;

extern void sut_tick_hook();
extern void sut_init_hook();

static sut_data_S sut_data;

void sut_init(void) {
    sut_init_hook();
}

void sut_tick(void) {
    sut_tick_hook();
}

void sut_set_data(const char* tag, const void* data, uint32_t size) {
    sut_data.stateData.setData(tag, data, size);
}

void sut_get_data(const char* tag, void* buffer, uint32_t size) {
    sut_data.stateData.getData(tag, buffer, size);
}

#ifdef __cplusplus
}
#endif
