
# Simulator Framework for RTOS-Based Firmware

## Overview

This project provides a simulation framework that allows testing of RTOS-based firmware on a non-embedded target. It simulates firmware by creating a software-in-the-loop (SIL) environment using a C++ simulator, with Python wrappers for writing test cases. The framework is designed to isolate hardware dependencies and focuses on making the testing of firmware simple and effective without access to actual hardware.

## Directory Structure

```
/project_root
│
├── src/
│   ├── CMakeLists.txt           # Firmware build
│   ├── firmware.c               # Firmware hooks (init and tick)
│
├── sim/
│   ├── CMakeLists.txt           # Simulator and SWIG bindings
│   ├── SutState.hpp/.cpp        # Manages system under test state
│   ├── PeripheralInterface.hpp  # Interface for peripherals
│   ├── PeripheralInterfaceMap.hpp/.cpp # Maps peripherals
│   ├── Simulator.hpp/.cpp       # Simulator logic
│   ├── simulator.i              # SWIG interface for Python
│   ├── firmware_deps/           # Firmware-dependent code (e.g., TemperatureSensor)
│       ├── CMakeLists.txt       # CMake for firmware dependencies
│       ├── initializePeripherals.cpp # Initializes firmware-dependent peripherals
│       ├── TemperatureSensor.hpp/.cpp # Example peripheral
│
├── test/
│   ├── CMakeLists.txt           # For building and testing
│   ├── test_temperature_update.py  # Python test using pytest
│   ├── sim_artifacts/           # Holds generated SWIG wrappers and shared libraries
```

## Setting Up

### Prerequisites

- **CMake**: Version 3.10 or higher
- **Python 3**: Python 3.x with development libraries
- **SWIG**: SWIG for generating Python wrappers from C++ code

### Build Instructions

1. **Clone the repository**:
   ```bash
   git clone <repo_url>
   cd project_root
   ```

2. **Create a build directory and run CMake**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run Python tests**:
   Navigate to the `test` directory and run the Python tests using `pytest`.

   ```bash
   cd ../test
   pytest
   ```

## Porting to New Firmware

### Steps to Port

1. **Add firmware-dependent code**:
   - Place any new peripheral implementation inside the `sim/firmware_deps/` directory.
   - Implement the new peripheral in `initializePeripherals.cpp`.

2. **No changes are required in the simulator core**:
   - The `PeripheralInterfaceMap` in the simulator core will automatically initialize peripherals defined in `firmware_deps`.
   - `SutState` will interact with the initialized peripherals.

### Example of Adding a New Peripheral

1. Add a new peripheral class in `firmware_deps`, such as `PressureSensor.hpp` and `PressureSensor.cpp`.
2. Modify `initializePeripherals.cpp` to register the new peripheral:
   ```cpp
   peripherals["pressure_sensor"] = std::make_shared<PressureSensor>();
   ```

This modular design ensures that new peripherals can be integrated without modifying the core simulator logic.
