#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

void initSim(const char* sut_name, const char* lib_path);
void runTick();

void setSutDataFloat(const char* tag, float value);
void setSutDataInt32(const char* tag, int32_t value);
void setSutDataUInt32(const char* tag, uint32_t value);
void setSutDataBool(const char* tag, bool value);

float    getSutDataFloat(const char* tag);
int32_t  getSutDataInt32(const char* tag);
uint32_t getSutDataUInt32(const char* tag);
bool     getSutDataBool(const char* tag);

#ifdef __cplusplus
}
#endif
