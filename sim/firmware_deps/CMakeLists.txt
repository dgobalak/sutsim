# Firmware-specific dependencies
set(FIRMWARE_DEPS_SRC
    initializePeripherals.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(firmware_deps ${FIRMWARE_DEPS_SRC})

target_include_directories(firmware_deps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
