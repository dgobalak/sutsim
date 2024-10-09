# Create a configuration interface library for FreeRTOS
add_library(freertos_config INTERFACE)

# Include the FreeRTOS headers through this interface
target_include_directories(freertos_config SYSTEM INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/port/sutsim
    ${SUTSIM_FIRMWARE_FREERTOS_CONFIG_PATH}
)

# Add configuration macros for FreeRTOS (e.g., disabling coverage test)
target_compile_definitions(freertos_config INTERFACE
    projCOVERAGE_TEST=0
)

# Custom port sources and headers
add_library(freertos_kernel_port OBJECT)
target_sources(freertos_kernel_port PRIVATE
    port/sutsim/port.c
)

# Interface library for the custom port headers
add_library(freertos_kernel_port_headers INTERFACE)
target_include_directories(freertos_kernel_port_headers INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/port/sutsim
)

# Link port headers and config headers to the FreeRTOS port object library
target_link_libraries(freertos_kernel_port PRIVATE
    freertos_kernel_port_headers
    freertos_kernel_include
)

# Set the FreeRTOS heap and port settings as cache variables
set(FREERTOS_HEAP "4" CACHE STRING "Specify which FreeRTOS heap to use" FORCE)
set(FREERTOS_PORT "A_CUSTOM_PORT" CACHE STRING "Specify the FreeRTOS port" FORCE)

# Add the FreeRTOS kernel directory (from the FreeRTOS repo) as a subdirectory
set(FREERTOS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/kernel)
add_subdirectory(${FREERTOS_PATH})

# Link the FreeRTOS kernel and custom port into a final FreeRTOS library
# Assuming that the kernel subdirectory builds a freertos_kernel library
add_library(freertos_with_port INTERFACE)

# Include the kernel sources and the custom port into freertos_with_port
target_link_libraries(freertos_with_port INTERFACE
    freertos_kernel               # Kernel sources from FreeRTOS repo
    freertos_kernel_port          # Custom port files (OBJECT library)
    freertos_config               # Configuration settings for FreeRTOS
)
