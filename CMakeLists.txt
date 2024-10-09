cmake_minimum_required(VERSION 3.10)

# Set the Python version and find required packages
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(SWIG REQUIRED)

# Enable C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add subdirectories for src, sim, and test
add_subdirectory(sim)
add_subdirectory(libs/freertos)
add_subdirectory(libs/sutsim/c)

foreach(FIRMWARE_DIR ${SUTSIM_FIRMWARE_DIRS})
    add_subdirectory(${FIRMWARE_DIR})
endforeach()
