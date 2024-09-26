#pragma once

#include "PeripheralInterface.hpp"
#include <cstring>
#include <stdexcept>

class TemperatureSensor : public PeripheralInterface {
public:
    TemperatureSensor() : status_flags(0), temperature(0.0f) {}

    void setDataByTag(const std::string& element, const void* data, uint32_t size) override {
        if (element == "temperature" && size == sizeof(float)) {
            std::memcpy(&temperature, data, sizeof(float));
        } else {
            throw std::invalid_argument("Invalid data element or size for temperature sensor");
        }
    }

    void getDataByTag(const std::string& element, void* buffer, uint32_t size) const override {
        if (element == "temperature" && size == sizeof(float)) {
            std::memcpy(buffer, &temperature, sizeof(float));
        } else {
            throw std::invalid_argument("Invalid data element or size for temperature sensor");
        }
    }

    void setStatusFlags(uint32_t flags) override {
        status_flags = flags;
    }

    uint32_t getStatusFlags() const override {
        return status_flags;
    }

private:
    float temperature;
    uint32_t status_flags;
};
