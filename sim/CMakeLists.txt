# Set policies for SWIG handling
cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Include Python directories and simulator headers
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
include_directories(${Python3_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

# List of source files for the simulator
set(SIM_SRC
    SutState.cpp
    Simulator.cpp
    simulator_binding.cpp
    PeripheralInterface.hpp
    PeripheralInterfaceMap.cpp
)

# Generate SWIG wrapper
set(CMAKE_SWIG_FLAGS "")
set(SWIG_INTERFACE simulator.i)

# SWIG output files
set_source_files_properties(${SWIG_INTERFACE} PROPERTIES CPLUSPLUS ON)
swig_add_library(simulator_module LANGUAGE python SOURCES ${SWIG_INTERFACE} ${SIM_SRC})

# Link the SWIG-generated module with Python libraries
swig_link_libraries(simulator_module ${Python3_LIBRARIES})

# Output the Python module and shared libraries to test/sim_artifacts
set_target_properties(simulator_module PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../test/sim_artifacts
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../test/sim_artifacts
)

# Add firmware_deps
add_subdirectory(firmware_deps)

# Make sure the firmware_deps library is linked
target_link_libraries(simulator_module firmware_deps)

# Copy the Python simulator.py file to the test/sim_artifacts directory
add_custom_command(TARGET simulator_module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/simulator.py ${CMAKE_BINARY_DIR}/../test/sim_artifacts/
)
