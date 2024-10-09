cmake_minimum_required(VERSION 3.10)

project(dg-sim-example)

set(SUTSIM_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(SUTSIM_FIRMWARE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
set(SUTSIM_FIRMWARE_FREERTOS_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(.. build)