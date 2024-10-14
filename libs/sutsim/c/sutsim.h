#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Supported data types for tags
typedef enum {
    SUTSIM_INT32 = 0,
    SUTSIM_UINT32,
    SUTSIM_FLOAT,
    SUTSIM_BOOL
} sutsim_dataType_E;

typedef void (*sutsim_TagCallback)(const char* tag, const void* data, uint32_t size);

// forward declaration
typedef struct sutsim_tagEntry sutsim_tagEntry_S;

typedef struct sutsim_tagEntry {
    const char* tag;

    void* data;
    uint32_t data_size;
    sutsim_dataType_E data_type;

    sutsim_TagCallback subscriber_cb;  // Callback for firmware writes

    bool is_persistent;

    sutsim_tagEntry_S* next;
} sutsim_tagEntry_S;

typedef struct {
    bool initialized;
    sutsim_tagEntry_S* head;
    sutsim_tagEntry_S* tail;
    uint32_t count;
} sutsim_tagList_S;

// Initialize the simulator
void sutsim_init(void);

void sutsim_tick(void);

// Add a tag entry
bool sutsim_add_tag(const char* tag, void* data, uint32_t size, sutsim_dataType_E type, sutsim_TagCallback subscriber_cb, bool is_persistent);

// Subscribe to a tag (register a callback for tag updates)
bool sutsim_subscribe_to_tag(const char* tag, sutsim_TagCallback subscriber_cb);

// Write data to a tag
bool sutsim_write(const char* tag, const void* data, uint32_t size);

// Read data from the tag
bool sutsim_read(const char* tag, void* buffer, uint32_t size);

// Get the data type of a tag
int8_t sutsim_get_tag_type(const char* tag);
