#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION            0  // No preemption (single-threaded)
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configCPU_CLOCK_HZ              ( ( unsigned long ) 1000000 )
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES            1
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 10 * 1024 ) ) // Simulated heap size
#define configMAX_TASK_NAME_LEN         ( 10 )
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         0
#define configUSE_MUTEXES               1
#define configQUEUE_REGISTRY_SIZE       0
#define configCHECK_FOR_STACK_OVERFLOW  0
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_MALLOC_FAILED_HOOK    0
#define configSUPPORT_STATIC_ALLOCATION 1

// Hook function definitions
#define configASSERT(x) if ((x) == 0) { while(1); }

// Disable task-related features
#define INCLUDE_vTaskPrioritySet        0
#define INCLUDE_vTaskDelete             0
#define INCLUDE_vTaskSuspend            0
#define INCLUDE_xResumeFromISR          0
#define INCLUDE_vTaskDelayUntil         0
#define INCLUDE_vTaskDelay              0

#endif /* FREERTOS_CONFIG_H */
