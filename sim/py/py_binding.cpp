#include "py_binding.h"
#include "Simulator.hpp"
#include "StateTag.hpp"

#include <Python.h>
#include <cstring>  // For strcmp
#include <stdexcept>

static Simulator simulator;

void initSim(const char* sut_name, const char* lib_path) {
    simulator.init_sut(std::string(sut_name), std::string(lib_path));
}

void runTick() {
    simulator.tick_sut();
}

void setSutDataFloat(const char* tag, float value) {
    const StateTag state_tag{tag};
    simulator.setSutData(state_tag, &value, "float");
}

void setSutDataInt32(const char* tag, int32_t value) {
    const StateTag state_tag{tag};
    simulator.setSutData(state_tag, &value, "int32");
}

void setSutDataUInt32(const char* tag, uint32_t value) {
    const StateTag state_tag{tag};
    simulator.setSutData(state_tag, &value, "uint32");
}

void setSutDataBool(const char* tag, bool value) {
    const StateTag state_tag{tag};
    simulator.setSutData(state_tag, &value, "bool");
}

float getSutDataFloat(const char* tag) {
    float value = 0.0f;
    StateTag state_tag{tag};
    simulator.getSutData(state_tag, &value, "float");
    return value;
}

int32_t getSutDataInt32(const char* tag) {
    int32_t value = 0;
    StateTag state_tag{tag};
    simulator.getSutData(state_tag, &value, "int32");
    return value;
}

uint32_t getSutDataUInt32(const char* tag) {
    uint32_t value = 0;
    StateTag state_tag{tag};
    simulator.getSutData(state_tag, &value, "uint32");
    return value;
}

bool getSutDataBool(const char* tag) {
    bool value = false;
    StateTag state_tag{tag};
    simulator.getSutData(state_tag, &value, "bool");
    return value;
}

void setSutData(const char* tag, PyObject* value) {
    if (PyFloat_Check(value)) {
        setSutDataFloat(tag, (float)PyFloat_AsDouble(value));
    } else if (PyLong_Check(value)) {
        long v = PyLong_AsLong(value);
        if (v >= 0) {
            setSutDataUInt32(tag, (uint32_t)v);
        } else {
            setSutDataInt32(tag, (int32_t)v);
        }
    } else if (PyBool_Check(value)) {
        setSutDataBool(tag, PyObject_IsTrue(value));
    } else {
        PyErr_SetString(PyExc_TypeError, "Unsupported data type for setSutData");
    }
}

PyObject* getSutData(const char* tag) {
    if (simulator.getSutDataType(std::string(tag)) == "float") {
        return PyFloat_FromDouble(getSutDataFloat(tag));
    } else if (simulator.getSutDataType(std::string(tag)) == "int32") {
        return PyLong_FromLong(getSutDataInt32(tag));
    } else if (simulator.getSutDataType(std::string(tag)) == "uint32") {
        return PyLong_FromUnsignedLong(getSutDataUInt32(tag));
    } else if (simulator.getSutDataType(std::string(tag)) == "bool") {
        return PyBool_FromLong(getSutDataBool(tag));
    } else {
        PyErr_SetString(PyExc_TypeError, "Unsupported data type for getSutData");
        return NULL;
    }
}
