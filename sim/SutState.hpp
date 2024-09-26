#pragma once

#include "PeripheralInterfaceMap.hpp"
#include <memory>
#include <unordered_map>
#include <string>

class SutState {
public:
    SutState();

    void setData(const std::string& tag, const void* data, uint32_t size);
    void getData(const std::string& tag, void* buffer, uint32_t size) const;

private:
    std::shared_ptr<PeripheralInterfaceMap> peripheral_map;

    std::pair<std::string, std::string> splitTag(const std::string& tag) const;
};
