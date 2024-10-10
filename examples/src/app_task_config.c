#include "task_config.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

extern void taskFunction_readTemperature_init_100Hz(void);
extern void taskFunction_readTemperature_run_100Hz(void);
extern void taskFunction_processTemperature_eventDriven(void);

static taskConfig_S task_config[] = {
    {
        .type = TASK_TYPE_PERIODIC,
        .period_ms = 10,
        .task_init_func = taskFunction_readTemperature_init_100Hz,
        .task_run_func = taskFunction_readTemperature_run_100Hz,
    },
    {
        .type = TASK_TYPE_EVENT_DRIVEN,
        .task_init_func = NULL,
        .task_run_func = taskFunction_processTemperature_eventDriven,
    }
};

taskConfigList_S task_config_list = {
    .task_config = task_config,
    .task_count = sizeof(task_config) / sizeof(taskConfig_S),
};
