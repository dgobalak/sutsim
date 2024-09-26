#include "simulator_binding.h"
#include "Simulator.hpp"
#include <cstring>  // For strcmp
#include <stdexcept>

Simulator simulator;  // Define simulator instance here, only once.

void initSimulator(const char* lib_path) {
    simulator.init(std::string(lib_path));
}

void runTick() {
    simulator.runTick();
}

// void set_sut_data(const char* tag, const void* data, uint32_t size) {
//     simulator.getSutState().setData(std::string(tag), data, size);
// }

// void get_sut_data(const char* tag, void* buffer, uint32_t size) {
//     simulator.getSutState().getData(std::string(tag), buffer, size);
// }


// Python wrappers
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
