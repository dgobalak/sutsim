#pragma once

#include "PeripheralInterface.hpp"
#include <memory>
#include <unordered_map>
#include <string>

class PeripheralInterfaceMap {
public:
    PeripheralInterfaceMap();

    std::shared_ptr<PeripheralInterface> getPeripheral(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<PeripheralInterface>> peripherals;

    void initializePeripherals();
};
