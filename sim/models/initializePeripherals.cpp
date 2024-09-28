#include "PeripheralInterfaceMap.hpp"
#include "TemperatureSensor.hpp"

void PeripheralInterfaceMap::initializePeripherals() {
    peripherals["temperature_sensor"] = std::make_shared<TemperatureSensor>();
}
