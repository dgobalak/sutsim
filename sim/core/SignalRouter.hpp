#pragma once

#include "SignalRoute.hpp"
#include <vector>
#include <cstdint>

class SignalRouter {
public:
    void addSignalRoute(const std::string& tag, std::function<void*()> signal_cb, uint32_t period_ms, void (*sutsim_write_cb)(const char* tag, const void* data, uint32_t size)) {
        routes_.emplace_back(tag, signal_cb, period_ms, sutsim_write_cb);
    }

    void tick(uint32_t current_time_ms) {
        for (auto& route : routes_) {
            route.tryExecute(current_time_ms);
        }
    }

private:
    std::vector<SignalRoute> routes_;  // Collection of signal routes
};
