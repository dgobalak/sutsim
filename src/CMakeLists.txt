# Create a shared library for the firmware
add_library(firmware SHARED firmware.c)

# Assuming the firmware library is named libfirmware.so
add_custom_command(TARGET firmware POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:firmware> ${CMAKE_BINARY_DIR}/../test/sim_artifacts/
)
