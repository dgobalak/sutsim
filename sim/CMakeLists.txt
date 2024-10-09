# Set policies to resolve warnings
cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
include_directories(${Python3_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})


# Simulator core
add_library(simulator_core
    core/Simulator.cpp
    core/SutContext.hpp
    core/Simulator.hpp
)

add_library(py_binding
    py/py_binding.cpp
    py/py_binding.h
)

# Add include directories for models to access firmware_conn headers
target_include_directories(py_binding PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core ${CMAKE_CURRENT_SOURCE_DIR}/py)
target_include_directories(simulator_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)

# Set up Python bindings
set(CMAKE_SWIG_FLAGS "")
set(SWIG_INTERFACE py/py_binding.i)

set_source_files_properties(${SWIG_INTERFACE} PROPERTIES CPLUSPLUS ON)

# Generate the SWIG interface for Python
swig_add_library(py_simulator
    LANGUAGE python
    SOURCES ${SWIG_INTERFACE} py/py_binding.cpp core/Simulator.cpp
)

# Link the SWIG bindings to the simulator core and firmware_conn
swig_link_libraries(py_simulator 
    ${Python3_LIBRARIES}
    simulator_core 
    py_binding
)

file(MAKE_DIRECTORY ${SUTSIM_TEST_DIR}/sim_artifacts)

set_target_properties(py_simulator PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${SUTSIM_TEST_DIR}/sim_artifacts
    RUNTIME_OUTPUT_DIRECTORY ${SUTSIM_TEST_DIR}/sim_artifacts
)

add_custom_command(TARGET py_simulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/sutsim.py ${SUTSIM_TEST_DIR}/sim_artifacts/
)

# Set the path to the sim_artifacts directory (where the SWIG Python module is generated)
set(SIM_ARTIFACTS_DIR "${SUTSIM_TEST_DIR}/sim_artifacts")

# Generate the run_tests.sh script to run tests with the correct PYTHONPATH
file(WRITE ${SUTSIM_TEST_DIR}/run_tests.sh
"#!/bin/bash\n"
"# Auto-generated script to run tests with correct PYTHONPATH\n"
"export PYTHONPATH=${SIM_ARTIFACTS_DIR}:\$PYTHONPATH\n"
"CMD_WRAPPER=\$\{CMD_WRAPPER\:-\}\n"
"$CMD_WRAPPER python -m pytest\n"
"if [ \$? -eq 0 ]; then\n"
"    echo 'All tests passed!'\n"
"else\n"
"    echo 'Some tests failed. Check the output above for details.'\n"
"fi\n"
)

# Make the run_tests.sh script executable
file(COPY ${SUTSIM_TEST_DIR}/run_tests.sh
     DESTINATION ${SUTSIM_TEST_DIR}
     FILE_PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
