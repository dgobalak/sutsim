#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void sut_init(void);
void sut_tick(void);
void sut_set_data(const char* tag, const void* data, uint32_t size);
void sut_get_data(const char* tag, void* buffer, uint32_t size);

#ifdef __cplusplus
}
#endif
