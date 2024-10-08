#include "Simulator.hpp"
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
#include <vector>

Simulator::Simulator() {
    // Initialize the simulator
    // std::cout << "Simulator initialized" << std::endl;
}

Simulator::~Simulator() {
    for (auto& context : sut_contexts) {
        if (context.second.initialized) {
            dlclose(context.second.lib_handle);
        }
    }
}

void Simulator::init_sut(const std::string& sut_name, const std::string& lib_path) {
    SutContext context;
    
    // Dynamically load the shared library for this SUT
    context.lib_handle = dlopen(lib_path.c_str(), RTLD_NOW);
    if (!context.lib_handle) {
        std::cerr << "Error loading firmware shared object: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }

    // // Load the required symbols from the SUT library
    context.sutsim_init = reinterpret_cast<void (*)()>(dlsym(context.lib_handle, "sutsim_init"));
    context.sutsim_tick = reinterpret_cast<void (*)()>(dlsym(context.lib_handle, "sutsim_tick"));
    context.sutsim_read = reinterpret_cast<bool (*)(const char*, void*, uint32_t)>(dlsym(context.lib_handle, "sutsim_read"));
    context.sutsim_write = reinterpret_cast<bool (*)(const char*, const void*, uint32_t)>(dlsym(context.lib_handle, "sutsim_write"));
    context.sutsim_subscribe_to_tag = reinterpret_cast<void (*)(const char*, void*)>(dlsym(context.lib_handle, "sutsim_subscribe_to_tag"));

    if (!context.sutsim_init || !context.sutsim_tick || !context.sutsim_read || !context.sutsim_write || !context.sutsim_subscribe_to_tag) {
        throw std::runtime_error("Failed to load required symbols from SUT library.");
    }

    // // Initialize the SUT
    context.sutsim_init();
    context.initialized = true;
    
    // // Store the SUT context
    sut_contexts[sut_name] = context;
}

void Simulator::tick_sut() {
    for (auto& context : sut_contexts) {
        if (context.second.initialized) {
            context.second.sutsim_tick();
        }
    }
}

void Simulator::setSutData(const std::string& tag, const void* value, const std::string& type) {
    std::string sut_name, sut_tag;
    std::tie(sut_name, sut_tag) = splitTag(tag);
    
    if (sut_contexts.find(sut_name) == sut_contexts.end()) {
        throw std::invalid_argument("SUT not found");
    }

    if (sut_contexts[sut_name].sutsim_write == nullptr) {
        throw std::invalid_argument("SUT does not support set data");
    }
    
    if (type == "float") {
        sut_contexts[sut_name].sutsim_write(sut_tag.c_str(), value, sizeof(float));
    } else if (type == "int32") {
        sut_contexts[sut_name].sutsim_write(sut_tag.c_str(), value, sizeof(int32_t));
    } else if (type == "uint32") {
        sut_contexts[sut_name].sutsim_write(sut_tag.c_str(), value, sizeof(uint32_t));
    } else if (type == "bool") {
        sut_contexts[sut_name].sutsim_write(sut_tag.c_str(), value, sizeof(bool));
    } else {
        throw std::invalid_argument("Unsupported type");
    }
}

void Simulator::getSutData(const std::string& tag, void* value, const std::string& type) {
    std::string sut_name, sut_tag;
    std::tie(sut_name, sut_tag) = splitTag(tag);
    
    if (sut_contexts.find(sut_name) == sut_contexts.end()) {
        throw std::invalid_argument("SUT not found");
    }

    if (sut_contexts[sut_name].sutsim_read == nullptr) {
        throw std::invalid_argument("SUT does not support get data");
    }
    
    if (type == "float") {
        sut_contexts[sut_name].sutsim_read(sut_tag.c_str(), value, sizeof(float));
    } else if (type == "int32") {
        sut_contexts[sut_name].sutsim_read(sut_tag.c_str(), value, sizeof(int32_t));
    } else if (type == "uint32") {
        sut_contexts[sut_name].sutsim_read(sut_tag.c_str(), value, sizeof(uint32_t));
    } else if (type == "bool") {
        sut_contexts[sut_name].sutsim_read(sut_tag.c_str(), value, sizeof(bool));
    } else {
        throw std::invalid_argument("Unsupported type");
    }
}

std::pair<std::string, std::string> Simulator::splitTag(const std::string& tag) const {
    size_t pos = tag.find('.');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid tag format");
    }
    return std::make_pair(tag.substr(0, pos), tag.substr(pos + 1));
}
