cmake_minimum_required(VERSION 3.10)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/default_options.cmake)

# Set the Python version and find required packages
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(SWIG REQUIRED)

# Enable C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add subdirectories for src, sim, and test
add_subdirectory(sim)
add_subdirectory(libs/sutsim/c)

if (SUTSIM_ENABLE_TASK_CONFIG STREQUAL "ON")
    add_subdirectory(libs/task_config)
endif()

if (SUTSIM_ENABLE_PROVIDED_FREERTOS STREQUAL "ON")
    add_subdirectory(libs/freertos)
endif()

foreach(FIRMWARE_DIR ${SUTSIM_FIRMWARE_DIRS})
    add_subdirectory(${FIRMWARE_DIR})
endforeach()
