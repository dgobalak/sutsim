#ifndef PORTMACRO_H
#define PORTMACRO_H

#include <stdint.h>

#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        long
#define portSHORT       short
#define portSTACK_TYPE  uint32_t
#define portBASE_TYPE   int

typedef portSTACK_TYPE StackType_t;
typedef int BaseType_t;
typedef unsigned int UBaseType_t;
typedef uint32_t TickType_t;

#define portMAX_DELAY ( TickType_t ) 0xffffffffUL

// Disable/enable interrupts (no-op for simulation)
#define portDISABLE_INTERRUPTS()    /* No-op */
#define portENABLE_INTERRUPTS()     /* No-op */

// Critical section management (no-op for simulation)
#define portENTER_CRITICAL()        /* No-op */
#define portEXIT_CRITICAL()         /* No-op */

// Scheduler management (no-op, since we won't start the scheduler)
#define portYIELD()                 /* No-op */
#define portNOP()                   /* No-op */

// These are architecture-specific, but we won't use them in the simulation
#define portSTACK_GROWTH            (-1)
#define portTICK_PERIOD_MS          ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT          4

#endif /* PORTMACRO_H */
