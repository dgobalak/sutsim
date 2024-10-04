#pragma once

#include "PeripheralInterface.hpp"
#include <cstring>
#include <stdexcept>

class TemperatureSensor : public PeripheralInterface {
public:
    TemperatureSensor() : temperature(0.0f), overTemperatureThreshold(0.0) {}

    void setDataByTag(const std::string& element, const void* data, uint32_t size) override {
        if (element == "temperature" && size == sizeof(float)) {
            std::memcpy(&temperature, data, sizeof(float));
        } 
        else if (element == "overTemperatureThreshold" && size == sizeof(float)) {
            std::memcpy(&overTemperatureThreshold, data, sizeof(float));
        } 
        else {
            throw std::invalid_argument("Invalid data element or size for temperature sensor");
        }
    }

    void getDataByTag(const std::string& element, void* buffer, uint32_t size) const override {
        if (element == "temperature" && size == sizeof(float)) {
            std::memcpy(buffer, &temperature, sizeof(float));
        }
        else if (element == "overTemperatureThreshold" && size == sizeof(float)) {
            std::memcpy(buffer, &overTemperatureThreshold, sizeof(float));
        } 
        else {
            throw std::invalid_argument("Invalid data element or size for temperature sensor");
        }
    }

private:
    float    temperature;
    float    overTemperatureThreshold;
};
