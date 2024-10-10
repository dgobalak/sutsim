#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    TASK_TYPE_PERIODIC,
    TASK_TYPE_EVENT_DRIVEN
} taskType_E;

typedef void (*task_init_func)(void);
typedef void (*task_run_func)(void);

typedef struct {
    taskType_E                type;
    uint32_t                  period_ms;                 // Period for periodic tasks
    task_init_func            task_init_func;            // Runs before task infinite loop
    task_run_func             task_run_func;             // Runs in the infinite loop
} taskConfig_S;

typedef struct {
    taskConfig_S* task_config;
    uint32_t task_count;
} taskConfigList_S;

void task_executeAllInit(void);
void task_executeAll(uint32_t tickCounter_ms);
