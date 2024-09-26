#include "Simulator.hpp"
#include <iostream>
#include <dlfcn.h>

Simulator::Simulator() : firmware_run_tick_hook(nullptr), firmware_init_hook(nullptr), init_done(false) {}

Simulator::~Simulator() {
    terminate();
}

void Simulator::init(const std::string& library_path) {
    void* handle = dlopen(library_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading firmware shared object: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }

    firmware_run_tick_hook = reinterpret_cast<void (*)(void)>(dlsym(handle, "run_tick_hook"));
    firmware_init_hook = reinterpret_cast<void (*)(void)>(dlsym(handle, "init_hook"));

    if (firmware_init_hook) {
        firmware_init_hook();
        init_done = true;
    }
}

void Simulator::runTick() {
    if (!init_done) {
        std::cerr << "Error: init_hook has not been called.\n";
        return;
    }

    if (firmware_run_tick_hook) {
        firmware_run_tick_hook();  // Call the firmware's tick hook
    }
}

void Simulator::terminate() {
    std::cout << "Simulator terminated.\n";
}

SutState& Simulator::getSutState() {
    return sut_state;
}

void Simulator::setSutData(const std::string& tag, const void* value, const std::string& type) {
    if (type == "float") {
        sut_state.setData(tag, value, sizeof(float));
    } else if (type == "int32") {
        sut_state.setData(tag, value, sizeof(int32_t));
    } else if (type == "uint32") {
        sut_state.setData(tag, value, sizeof(uint32_t));
    } else if (type == "bool") {
        sut_state.setData(tag, value, sizeof(bool));
    } else {
        throw std::invalid_argument("Unsupported type");
    }
}

void Simulator::getSutData(const std::string& tag, void* value, const std::string& type) {
    if (type == "float") {
        sut_state.getData(tag, value, sizeof(float));
    } else if (type == "int32") {
        sut_state.getData(tag, value, sizeof(int32_t));
    } else if (type == "uint32") {
        sut_state.getData(tag, value, sizeof(uint32_t));
    } else if (type == "bool") {
        sut_state.getData(tag, value, sizeof(bool));
    } else {
        throw std::invalid_argument("Unsupported type");
    }
}
