#include "task_config.h"
#include <stdlib.h>

extern taskConfigList_S task_config_list;

void task_tryRunningAll(uint32_t tickCounter_ms) {
    for (uint32_t i = 0; i < task_config_list.task_count; i++) {
        taskConfig_S* task = &task_config_list.task_config[i];

        if (task->type == TASK_TYPE_PERIODIC) {
            if (tickCounter_ms % task->period_ms != 0) {
                continue;
            }
        }

        // Run any task code before the infinite loop
        if (!task->initComplete) {
            if (task->task_init_func) {
                task->task_init_func();
            }
            task->initComplete = true;
        }

        switch (task->type) {
            case TASK_TYPE_PERIODIC:
                if (task->periodic_task.task_periodic_run_func) {
                    task->periodic_task.task_periodic_run_func();
                }
                break;
            case TASK_TYPE_EVENT_DRIVEN:
                if (task->event_driven_task.task_condition_setup_func) {
                    task->event_driven_task.task_condition_setup_func();
                }

                if (task->event_driven_task.task_condition_check_func) {
                    if (task->event_driven_task.task_condition_check_func()) {
                        task->event_driven_task.task_condition_run_func();
                    }
                }
                break;
        }
    }
}
