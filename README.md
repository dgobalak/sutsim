
# Firmware Simulation Environment

This project simulates embedded firmware using a dynamically loaded shared library. It supports running firmware logic within a simulation framework and provides Python bindings (via SWIG) to allow testing and interaction from Python. The project allows multiple System Under Test (SUT) instances to be simulated simultaneously.

## Directory Structure

```
.
├── build/                  # Build output directory
├── sim/
│   ├── core/               # Simulator core logic
│   ├── firmware_conn/      # Firmware connection interfaces and peripherals
│   ├── models/             # Peripheral models like sensors, etc.
│   ├── py/                 # SWIG interface and Python bindings
│   ├── CMakeLists.txt      # CMake configuration for the simulator and SWIG bindings
├── src/                    # Firmware source code
│   ├── CMakeLists.txt      # CMake configuration for the firmware
├── test/
│   ├── sim_artifacts/      # Contains shared libraries and generated Python bindings for testing
│   ├── test_temperature_update.py # Python tests for the simulation
│   ├── CMakeLists.txt      # CMake configuration for tests
├── CMakeLists.txt          # Root CMake file
└── README.md               # This README file
```

## Prerequisites

Make sure you have the following installed on your system:
- **CMake** (version 3.16 or higher)
- **GCC** (or Clang) with C++17 support
- **Python** (version 3.8 or higher)
- **Python development headers**:
  ```bash
  sudo apt-get install python3-dev
  ```
- **SWIG**:
  ```bash
  sudo apt-get install swig
  ```

## Building the Project

To build the project:

1. **Create the build directory**:
   ```bash
   mkdir build
   cd build
   ```

2. **Run CMake**:
   ```bash
   cmake ..
   ```

3. **Build the project**:
   ```bash
   make
   ```

This will compile the firmware, simulator, and SWIG Python bindings. All generated libraries will be placed in the `test/sim_artifacts` directory.

## Running Tests

Tests are written using **pytest** and can be run after building the project. Make sure to activate the Python environment with the generated bindings by running the tests inside the `test/` directory.

1. **Navigate to the `test` directory**:
   ```bash
   cd test
   ```

2. **Run the tests**:
   ```bash
   pytest
   ```

This will execute the Python tests that interact with the simulated firmware and peripherals.

## Debugging with gdb

If you encounter segmentation faults or other issues during the tests, you can use **gdb** to debug the shared library and Python bindings.

### Steps for Debugging with gdb:

1. **Build the project with debug symbols**:
   Re-run the CMake configuration to enable debug symbols.
   ```bash
   cd build
   cmake -DCMAKE_BUILD_TYPE=Debug ..
   make
   ```

2. **Run pytest under gdb**:
   Launch **gdb** and use it to run `pytest`:
   ```bash
   gdb --args python3 -m pytest
   ```

3. **Run the tests inside gdb**:
   In the gdb prompt, run:
   ```bash
   run
   ```

4. **Analyze the crash**:
   If the program crashes (e.g., segmentation fault), use the `bt` (backtrace) command to see where the crash occurred:
   ```bash
   bt
   ```

   The backtrace will show you the sequence of function calls that led to the crash, allowing you to identify the source of the issue in the C++ code.

### Example gdb Workflow:

1. Launch **gdb** with the Python test command:
   ```bash
   gdb --args python3 -m pytest
   ```

2. When the gdb prompt appears, run the test:
   ```bash
   run
   ```

3. If a segmentation fault occurs, use `bt` to print the backtrace:
   ```bash
   bt
   ```

4. Exit gdb after debugging:
   ```bash
   quit
   ```

## Example Test

Here's a simple Python test (`test_temperature_update.py`) that sets and retrieves values from the simulated firmware:

```python
import sutsim as simulator
import pytest
import os

def test_data_types():
    # Path to the firmware shared library
    firmware_lib_path = os.path.join(os.path.dirname(__file__), 'sim_artifacts', 'libfirmware.so')

    # Initialize the simulator
    simulator.initSim("device", firmware_lib_path)

    # Set different types of values
    simulator.set_sut_data_float("device.temperature_sensor.temperature", 25.5)  # float
    simulator.set_sut_data_uint32("device.temperature_sensor.overTemperatureThreshold", 1)

    # Run the firmware tick
    simulator.run_tick()

    # Get and assert values
    assert simulator.get_sut_data_float("device.temperature_sensor.temperature") == 25.5
    assert simulator.get_sut_data_uint32("device.temperature_sensor.overTemperatureThreshold") == 1
```

## Known Issues

- **Segmentation Faults**: These may happen due to incorrect initialization of C++ objects or improper linking of shared libraries. Use the `gdb` instructions provided above to debug any crashes.
- **Global Initialization**: Be careful with static or global initialization of C++ objects, as this can lead to crashes during module loading.

## License

[MIT License](LICENSE)
