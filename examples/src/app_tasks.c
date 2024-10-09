#include "task_config.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

extern void taskFunction_readTemperature_periodic(void);
extern bool taskFunction_handleTemperature_eventCheck(void);
extern void taskFunction_handleTemperature_eventRun(void);

static taskConfig_S task_config[] = {
    {
        .type = TASK_TYPE_PERIODIC,
        .period_ms = 1,
        .task_init_func = NULL,
        .periodic_task.task_periodic_run_func = taskFunction_readTemperature_periodic,
    },
    {
        .type = TASK_TYPE_EVENT_DRIVEN,
        .task_init_func = NULL,
        .event_driven_task.task_condition_setup_func = NULL,
        .event_driven_task.task_condition_check_func = taskFunction_handleTemperature_eventCheck,
        .event_driven_task.task_condition_run_func = taskFunction_handleTemperature_eventRun,
    }
};

taskConfigList_S task_config_list = {
    .task_config = task_config,
    .task_count = sizeof(task_config) / sizeof(taskConfig_S),
};
