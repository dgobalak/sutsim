
# SUTSim

SUTSim is a simulation environment for firmware that integrates well with Python tests. It allows you to execute firmware (without hardware), inject sensor data, and validate outputs (bus data, PWM signals, etc).

## Project Structure

The directory structure of the project is as follows:

```
/examples
    /src
    /test
        /sim_artifacts
        run_tests.sh
        test_temperature_sensor.py
/libs
    /freertos
    /sutsim
/sim
    /core
    /py
```

## Setup Instructions

### 1. Cloning the Repository

This project uses git submodules to manage dependencies. To clone the repository with all submodules, use the following commands:

```bash
git clone --recurse-submodules <repository-url>
cd <repository-folder>
```

If you already cloned the repo without the submodules, you can initialize them manually with:

```bash
git submodule update --init --recursive
```

### 2. Building the Project

The project uses CMake for its build process. Make sure you have CMake installed on your system.

```bash
mkdir build
cd build
cmake ..
make
```

### 3. Running the Tests

The tests are located in the `/test` directory. Use the following commands to execute the tests using `pytest`:

```bash
cd test
./run_tests.sh
```

This script sets up the environment variables needed for the tests and runs them using `pytest`. It ensures that the shared libraries are correctly loaded and the Python bindings are configured.

## Test Syntax

Here's an example test case that uses the new test syntax:

```python
import sutsim as simulator
import pytest
import os

def test_data_types():
    # Path to the firmware shared library
    firmware_lib_path = os.path.join(os.path.dirname(__file__), 'sim_artifacts', 'libfirmware.so')

    # Initialize the simulator
    simulator.initSim("device", firmware_lib_path)

    simulator.setSutDataFloat("device.temperature_sensor.temperature", 100.0)

    for _ in range(20):
        simulator.runTick()

    # # Get the temperature
    assert simulator.getSutDataFloat("device.temperature_sensor.temperature") == 100.0
```

## Debugging with GDB

To debug the tests or the firmware simulation with GDB, follow these steps:

1. Build the project:

   ```bash
   cd build
   cmake ..
   make
   ```

2. Run GDB with the Python test process:

   ```bash
   cd test
   CMD_WRAPPER="gdb --args" run_tests.sh
   ```

3. Set breakpoints and use GDB commands to debug the simulation and interactions.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
