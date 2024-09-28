#pragma once

#include <cstdint>
#include <string>

class SutContext {
public:
    SutContext() : lib_handle(nullptr), run_tick(nullptr), init_sut(nullptr), set_sut_data(nullptr), get_sut_data(nullptr) {}
    ~SutContext() = default;
    
    std::string sut_name;
    std::string sut_path;

    void* lib_handle;
    void (*run_tick)();
    void (*init_sut)();
    void (*set_sut_data)(const char*, const void*, uint32_t);
    void (*get_sut_data)(const char*, void*, uint32_t);

    bool initialized = false;
};
