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
    context.init_sut = reinterpret_cast<void (*)()>(dlsym(context.lib_handle, "sut_init"));
    context.run_tick = reinterpret_cast<void (*)()>(dlsym(context.lib_handle, "sut_tick"));
    context.set_sut_data = reinterpret_cast<void (*)(const char*, const void*, uint32_t)>(dlsym(context.lib_handle, "sut_set_data"));
    context.get_sut_data = reinterpret_cast<void (*)(const char*, void*, uint32_t)>(dlsym(context.lib_handle, "sut_get_data"));

    if (!context.init_sut) {
        throw std::runtime_error("Failed to load required symbols from SUT library.");
    }

    // // Initialize the SUT
    context.init_sut();
    context.initialized = true;
    
    // // Store the SUT context
    sut_contexts[sut_name] = context;
}

void Simulator::tick_sut() {
    for (auto& context : sut_contexts) {
        if (context.second.initialized) {
            context.second.run_tick();
        }
    }
}

void Simulator::setSutData(const std::string& tag, const void* value, const std::string& type) {
    std::string sut_name, sut_tag;
    std::tie(sut_name, sut_tag) = splitTag(tag);
    
    if (sut_contexts.find(sut_name) == sut_contexts.end()) {
        throw std::invalid_argument("SUT not found");
    }

    if (sut_contexts[sut_name].set_sut_data == nullptr) {
        throw std::invalid_argument("SUT does not support set data");
    }
    
    if (type == "float") {
        sut_contexts[sut_name].set_sut_data(sut_tag.c_str(), value, sizeof(float));
    } else if (type == "int32") {
        sut_contexts[sut_name].set_sut_data(sut_tag.c_str(), value, sizeof(int32_t));
    } else if (type == "uint32") {
        sut_contexts[sut_name].set_sut_data(sut_tag.c_str(), value, sizeof(uint32_t));
    } else if (type == "bool") {
        sut_contexts[sut_name].set_sut_data(sut_tag.c_str(), value, sizeof(bool));
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

    if (sut_contexts[sut_name].get_sut_data == nullptr) {
        throw std::invalid_argument("SUT does not support get data");
    }
    
    if (type == "float") {
        sut_contexts[sut_name].get_sut_data(sut_tag.c_str(), value, sizeof(float));
    } else if (type == "int32") {
        sut_contexts[sut_name].get_sut_data(sut_tag.c_str(), value, sizeof(int32_t));
    } else if (type == "uint32") {
        sut_contexts[sut_name].get_sut_data(sut_tag.c_str(), value, sizeof(uint32_t));
    } else if (type == "bool") {
        sut_contexts[sut_name].get_sut_data(sut_tag.c_str(), value, sizeof(bool));
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
