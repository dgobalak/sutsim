#include "SutState.hpp"
#include <cstring>
#include <sstream>
#include <stdexcept>

SutState::SutState() {
    peripheral_map = std::make_shared<PeripheralInterfaceMap>();
}

std::pair<std::string, std::string> SutState::splitTag(const std::string& tag) const {
    std::size_t pos = tag.find('.');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid tag format.");
    }
    return {tag.substr(0, pos), tag.substr(pos + 1)};
}

void SutState::setData(const std::string& tag, const void* data, uint32_t size) {
    auto [peripheral_name, element_name] = splitTag(tag);
    auto peripheral = peripheral_map->getPeripheral(peripheral_name);
    if (peripheral) {
        peripheral->setDataByTag(element_name, data, size);
    } else {
        throw std::invalid_argument("Peripheral not found.");
    }
}

void SutState::getData(const std::string& tag, void* buffer, uint32_t size) const {
    auto [peripheral_name, element_name] = splitTag(tag);
    auto peripheral = peripheral_map->getPeripheral(peripheral_name);
    if (peripheral) {
        peripheral->getDataByTag(element_name, buffer, size);
    } else {
        throw std::invalid_argument("Peripheral not found.");
    }
}
