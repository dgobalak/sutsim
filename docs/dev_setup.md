
# Development Environment Setup

Follow these steps to set up the development environment for the SUTSim project on a Linux machine. 

## 1. Prerequisites

Ensure the following dependencies are installed on your system:

- **Git**: Required for cloning the repository and managing submodules.
- **CMake**: Required for building the project.
- **Python**: Required for running Python tests.
- **Pytest**: Required for executing unit tests.
- **GCC/G++**: Required for compiling the project.
- **SWIG**: Required for generating Python bindings from C/C++ code.

You can install the required packages using the following commands:

```bash
sudo apt-get update
sudo apt-get install -y git cmake python3 python3-pip python3-dev gcc g++ swig
pip3 install pytest
```

## 2. Cloning the Repository

This project uses git submodules to manage dependencies. To clone the repository with all submodules, use the following commands:

```bash
git clone --recurse-submodules <repository-url>
cd <repository-folder>
```

If you have already cloned the repository without the submodules, initialize them manually with:

```bash
git submodule update --init --recursive
```

## 3. Building an example

1. Choose an example to build (I'll use basic_heater as an example):
   
   ```bash
   cd examples/basic_heater
   ```

2. Create a `build` directory and navigate into it:

   ```bash
   mkdir build
   cd build
   ```

3. Use CMake to generate the build files:

   ```bash
   cmake ..
   ```

4. Compile the project:

   ```bash
   make
   ```

## 4. Running Tests

1. Navigate to the `<example>/test` directory:

   ```bash
   cd ../test
   ```

2. Run the tests using the generated script:

   ```bash
   ./run_tests.sh
   ```

This script sets up the required environment variables and runs the tests using `pytest`.

## 5. Debugging with GDB

1. Build the project as described in the [Building the Project](#3-building-the-project) section.

2. Use the following command to run GDB with the Python test process:

   ```bash
   CMD_WRAPPER="gdb --args" ./run_tests.sh
   ```

3. You can now set breakpoints and use GDB commands to debug the firmware simulation.
