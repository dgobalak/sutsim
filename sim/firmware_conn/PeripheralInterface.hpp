#pragma once

#include <cstdint>
#include <string>

class PeripheralInterface {
public:
    virtual ~PeripheralInterface() = default;

    // Setter and getter for data by tag (e.g., "temperature")
    virtual void setDataByTag(const std::string& element, const void* data, uint32_t size) = 0;
    virtual void getDataByTag(const std::string& element, void* buffer, uint32_t size) const = 0;
};
