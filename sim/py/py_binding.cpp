#include "py_binding.h"
#include "Simulator.hpp"
#include <cstring>  // For strcmp
#include <stdexcept>

static Simulator simulator;  // Define simulator instance here, only once.

void initSim(const char* sut_name, const char* lib_path) {
    simulator.init_sut(std::string(sut_name), std::string(lib_path));
}

void runTick() {
    simulator.tick_sut();
}

void setSutDataFloat(const char* tag, float value) {
    simulator.setSutData(std::string(tag), &value, "float");
}

void setSutDataInt32(const char* tag, int32_t value) {
    simulator.setSutData(std::string(tag), &value, "int32");
}

void setSutDataUInt32(const char* tag, uint32_t value) {
    simulator.setSutData(std::string(tag), &value, "uint32");
}

void setSutDataBool(const char* tag, bool value) {
    simulator.setSutData(std::string(tag), &value, "bool");
}

float getSutDataFloat(const char* tag) {
    float value;
    simulator.getSutData(std::string(tag), &value, "float");
    return value;
}

int32_t getSutDataInt32(const char* tag) {
    int32_t value;
    simulator.getSutData(std::string(tag), &value, "int32");
    return value;
}

uint32_t getSutDataUInt32(const char* tag) {
    uint32_t value;
    simulator.getSutData(std::string(tag), &value, "uint32");
    return value;
}

bool getSutDataBool(const char* tag) {
    bool value;
    simulator.getSutData(std::string(tag), &value, "bool");
    return value;
}
