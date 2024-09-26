#pragma once

#include "SutState.hpp"
#include <memory>

class Simulator {
public:
    Simulator();
    ~Simulator();

    void init(const std::string& library_path);
    void runTick();
    void terminate();

    // Type-agnostic setter
    void setSutData(const std::string& tag, const void* value, const std::string& type);

    // Type-agnostic getter
    void getSutData(const std::string& tag, void* value, const std::string& type);

    SutState& getSutState();

private:
    SutState sut_state;
    void (*firmware_run_tick_hook)(void);
    void (*firmware_init_hook)(void);
    bool init_done;
};
