#pragma once

#include <cstdint>
#include <string>

class SutContext {
public:
    SutContext() : lib_handle(nullptr), sutsim_init(nullptr), sutsim_tick(nullptr), sutsim_subscribe_to_tag(nullptr), sutsim_write(nullptr), sutsim_read(nullptr), sutsim_get_tag_type(nullptr) {}
    ~SutContext() = default;
    
    std::string sut_name;
    std::string sut_path;

    void* lib_handle;
    void (*sutsim_init)(void);
    void (*sutsim_tick)(void);
    bool (*sutsim_subscribe_to_tag)(const char*, void*);
    bool (*sutsim_write)(const char*, const void*, uint32_t);
    bool (*sutsim_read)(const char*, void*, uint32_t);
    uint8_t (*sutsim_get_tag_type)(const char*);

    bool initialized = false;
};
