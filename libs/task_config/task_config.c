#include "task_config.h"
#include <stdlib.h>

extern taskConfigList_S task_config_list;

void task_executeAllInit(void) {
    for (uint32_t i = 0; i < task_config_list.task_count; i++) {
        taskConfig_S* task = &task_config_list.task_config[i];

        if (task->task_init_func) {
            task->task_init_func();
        }
    }
}

void task_executeAll(uint32_t tickCounter_ms) {
    for (uint32_t i = 0; i < task_config_list.task_count; i++) {
        taskConfig_S* task = &task_config_list.task_config[i];

        bool shouldRun = false;
        switch (task->type) {
            case TASK_TYPE_PERIODIC:
                shouldRun = (tickCounter_ms % task->period_ms) == 0;
                break;
            case TASK_TYPE_EVENT_DRIVEN:
                shouldRun = true;
                break;
            default:
                break;
        }

        if (shouldRun && task->task_run_func) {
            task->task_run_func();
        }
    }
}
