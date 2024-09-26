cmake_minimum_required(VERSION 3.10)

project(SimulatorProject)

# Set the Python version and find required packages
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(SWIG REQUIRED)

# Enable C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories for src, sim, and test
add_subdirectory(src)
add_subdirectory(sim)
add_subdirectory(test)
