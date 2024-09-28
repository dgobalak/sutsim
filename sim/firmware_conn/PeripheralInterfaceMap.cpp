#include "PeripheralInterfaceMap.hpp"

PeripheralInterfaceMap::PeripheralInterfaceMap() {
    initializePeripherals();
}

std::shared_ptr<PeripheralInterface> PeripheralInterfaceMap::getPeripheral(const std::string& name) const {
    auto it = peripherals.find(name);
    if (it != peripherals.end()) {
        return it->second;
    }
    return nullptr;
}
