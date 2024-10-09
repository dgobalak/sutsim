#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    TASK_TYPE_PERIODIC,
    TASK_TYPE_EVENT_DRIVEN
} taskType_E;

typedef void (*task_init_func)(void);
typedef void (*task_condition_setup_func)(void);
typedef void (*task_condition_run_func)(void);
typedef bool (*task_condition_check_func)(void);
typedef void (*task_periodic_run_func)(void);

typedef struct {
    taskType_E                type;
    uint32_t                  period_ms;                 // Period for periodic tasks
    task_init_func            task_init_func;            // Runs before task infinite loop
    union {
        struct {
            task_periodic_run_func task_periodic_run_func; // Runs each task loop
        } periodic_task;
        struct {
            task_condition_setup_func task_condition_setup_func; // Runs at start of each task loop
            task_condition_check_func task_condition_check_func; // Condition to check for event-driven tasks
            task_condition_run_func   task_condition_run_func;   // Runs each task loop if condition is true
        } event_driven_task;
    };

    bool initComplete;
} taskConfig_S;

typedef struct {
    taskConfig_S* task_config;
    uint32_t task_count;
} taskConfigList_S;

void task_tryRunningAll(uint32_t tickCounter_ms);
