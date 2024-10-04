#include "portmacro.h"

// No-op function for task yield
void vPortYield(void) {
    // No-op
}

// Critical section management (for single-threaded simulation)
void vTaskEnterCritical(void) {
    portENTER_CRITICAL();
}

void vTaskExitCritical(void) {
    portEXIT_CRITICAL();
}

// Scheduler startup (this will never actually run tasks)
BaseType_t xPortStartScheduler(void) {
    // Scheduler doesn't run in simulation, just return
    return 0;
}

void vPortEndScheduler(void) {
    // No-op
}
