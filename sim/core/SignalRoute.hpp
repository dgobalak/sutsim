#pragma once
#include <string>
#include <functional>
#include <cstdint>

class SignalRoute {
public:
    SignalRoute(const std::string& tag, std::function<void*()> signal_cb, uint32_t period_ms, void (*sutsim_write_cb)(const char* tag, const void* data, uint32_t size))
        : tag_(tag), signal_cb_(signal_cb), period_ms_(period_ms), last_execution_time_ms_(0), sutsim_write_cb_(sutsim_write_cb) {}

    // Method to check and execute the signal route
    void tryExecute(uint32_t current_time_ms) {
        if (current_time_ms - last_execution_time_ms_ >= period_ms_) {
            last_execution_time_ms_ = current_time_ms;
            void* signal_data = signal_cb_();
            sutsim_write_cb_(tag_.c_str(), signal_data, sizeof(signal_data));
        }
    }

private:
    std::string tag_;                       // Tag to route the signal data to
    
    std::function<void*()> signal_cb_;      // Callback to get the signal data
    void (*sutsim_write_cb_)(const char* tag, const void* data, uint32_t size);  // Callback to write the signal data to sutsim

    uint32_t period_ms_;                    // Period of the signal route in milliseconds
    uint32_t last_execution_time_ms_;       // Last time the signal route was executed
};
