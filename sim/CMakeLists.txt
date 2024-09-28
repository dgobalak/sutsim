file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../test/sim_artifacts)

# Set policies to resolve warnings
cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
include_directories(${Python3_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})


# Simulator core
add_library(simulator_core
    core/Simulator.cpp
    core/SutContext.hpp
    core/Simulator.hpp
)

# Peripheral interface and firmware connection code (firmware_conn)
add_library(firmware_conn
    firmware_conn/PeripheralInterface.hpp
    firmware_conn/PeripheralInterfaceMap.cpp
    firmware_conn/PeripheralInterfaceMap.hpp
    firmware_conn/sut_firmware.cpp
    firmware_conn/sut_firmware.h
    firmware_conn/SutState.cpp
    firmware_conn/SutState.hpp
)

# Models library (for peripherals and sensors)
add_library(models
    models/initializePeripherals.cpp
    models/TemperatureSensor.hpp
)

add_library(py_binding
    py/py_binding.cpp
    py/py_binding.h
)

# Add include directories for models to access firmware_conn headers
target_include_directories(models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/firmware_conn ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_include_directories(firmware_conn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/firmware_conn ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_include_directories(py_binding PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core ${CMAKE_CURRENT_SOURCE_DIR}/py)
target_include_directories(simulator_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)

# Set up Python bindings
set(CMAKE_SWIG_FLAGS "")
set(SWIG_INTERFACE py/py_binding.i)

set_source_files_properties(${SWIG_INTERFACE} PROPERTIES CPLUSPLUS ON)

# Generate the SWIG interface for Python
swig_add_library(py_simulator
    LANGUAGE python
    SOURCES ${SWIG_INTERFACE} py/py_binding.cpp core/Simulator.cpp models/initializePeripherals.cpp
)

# Link the SWIG bindings to the simulator core and firmware_conn
swig_link_libraries(py_simulator 
    ${Python3_LIBRARIES}
    simulator_core 
    models 
    py_binding
)

set_target_properties(py_simulator PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../test/sim_artifacts
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../test/sim_artifacts
)

add_custom_command(TARGET py_simulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/sutsim.py ${CMAKE_BINARY_DIR}/../test/sim_artifacts/
)
