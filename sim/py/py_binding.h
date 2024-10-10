#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <Python.h>

void initSim(const char* sut_name, const char* lib_path);
void runTick();

void setSutData(const char* tag, PyObject* value);
PyObject* getSutData(const char* tag);

#ifdef __cplusplus
}
#endif
