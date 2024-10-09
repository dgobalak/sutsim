add_library(task_config STATIC
    task_config.c
)

target_include_directories(task_config PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
