cmake_minimum_required(VERSION 3.10)

project(dg-sim-example)

set(SUTSIM_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(SUTSIM_FIRMWARE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(SUTSIM_RELATIVE_PATH ../..)
set(SUTSIM_BUILD_DIR build)

add_subdirectory(${SUTSIM_RELATIVE_PATH} ${SUTSIM_BUILD_DIR})
