# Integrating SUTSim with new project
So how do you integrate sutsim into an existing firmware codebase?

To help explain, I'll walk through the [basic_baremetal](https://github.com/dgobalak/sutsim/tree/main/examples/basic_baremetal) example since it's an example of the simplest possible sutsim integration.

There are 3 main components to the example.
1. A top-level CMakeLists.txt that configures and invokes the sutsim CMake scripts
2. A src/ directory
3. A test/ directory

## Top-level CMakeLists
```cmake
cmake_minimum_required(VERSION 3.10)

project(dg-sim-example)

set(SUTSIM_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(SUTSIM_FIRMWARE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(SUTSIM_RELATIVE_PATH ../..)
set(SUTSIM_BUILD_DIR build)

add_subdirectory(${SUTSIM_RELATIVE_PATH} ${SUTSIM_BUILD_DIR})
```

This CMake script configures some important parameters:
1. SUTSIM_TEST_DIR: Path to the test/ directory that contains all your test code
2. SUTSIM_FIRMWARE_DIRS: A list of firmware directories to build. SUTSim expects to find a CMakeLists.txt in each directory. Each CMakeLists.txt should build a shared object for a specific variant of your firmware.
3. SUTSIM_RELATIVE_PATH: Relative path at which the sutsim/ project can be found
4. SUTSIM_BUILD_DIR: The directory where build artifacts for the sim should be stored.

## src/
### Firmware CMakeLists.txt
Each firmware variant you want to simulate must have its own CMakeLists.txt that manages the shared object build. By compiling each firmware variant as a shared object, we can dynamically link it to the sutsim simulator. The script below shows a basic build for the example firmware. It defines all the files to be compiled, links the required sutsim C layer (note the use of the --whole-archive linker flag), and configures the build artifact directory (It's easier to manage if the shared object of every variant is stored in the same directory). 

```cmake
set(SOURCES
    sutsim_hooks.c
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(firmware SHARED ${SOURCES})
target_include_directories(firmware PRIVATE ${INCLUDE_DIRS})

target_link_libraries(firmware
    -Wl,--whole-archive sutsim -Wl,--no-whole-archive
)

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")

# Set output directory for firmware shared libraries
set_target_properties(firmware PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${SUTSIM_TEST_DIR}/sim_artifacts
)
```

### Required Hooks
The hooks that you're required to implement are sut_init_hook and sut_tick_hook. After the sutsim simulator loads a shared object, it uses these hooks to simulate the firmware running. At the beginning of the simulation, sut_init_hook is executed. Whenever you tick the simulation in a test, the sut_tick_hook is executed. Look at the [basic_heater example](https://github.com/dgobalak/sutsim/tree/main/examples/basic_heater) for more ideas on how to use these hooks.
```c
void sut_init_hook(void) {
  ...
}

void sut_tick_hook(void) {
  ...
}
```

## test/
### Configuring Tests
Typically, you should define a conftest.py file in your test directory. The sutsim Python framework expects the device_map fixture to be defined by the user. It needs to return a mapping from device/SUT names to their shared object path.
```python
from sutsim_fixtures import devices
import pytest
import os

@pytest.fixture
def device_map():
    # Map simulated device instances to their shared object firmware paths
    return {
        "dev1": os.path.join(os.path.dirname(__file__), 'sim_artifacts', 'libfirmware.so'),
    }
```

### Example Tests
The test below is a simple example of running firmware in simulation. Look at the [basic_heater example](https://github.com/dgobalak/sutsim/tree/main/examples/basic_heater) to learn more about what you can validate with sutsim (using more advanced features like signal injection and monitoring).
```python
import pytest

def test_baremetal(devices):    
    devices.run_for(10)
```
