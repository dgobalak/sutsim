#pragma once

#include <stdint.h>
#include <stdbool.h>

// Supported data types for tags
typedef enum {
    SUTSIM_INT32,
    SUTSIM_UINT32,
    SUTSIM_FLOAT,
    SUTSIM_BOOL
} sutsim_dataType_E;

typedef void (*sutsim_TagCallback)(const char* tag, const void* data, uint32_t size);

// forward declaration
typedef struct sutsim_tagEntry sutsim_tagEntry_S;

typedef struct sutsim_tagEntry {
    uint32_t id;  // Unique identifier for each tag
    const char* tag;
    void* data;  // Pointer to the user-provided data buffer
    uint32_t size;  // Size of the data buffer
    sutsim_dataType_E type;  // Data type of the tag
    sutsim_TagCallback subscriber_cb;  // Callback for firmware writes

    sutsim_tagEntry_S* next;      // Pointer to the next tag in the list
} sutsim_tagEntry_S;

// Linked list of tag entries
typedef struct {
    bool initialized;
    sutsim_tagEntry_S* head;
    sutsim_tagEntry_S* tail;
    uint32_t count;
} sutsim_tagList_S;

// Initialize the simulator
void sutsim_init(void);

void sutsim_tick(void);

// Add a tag entry (user provides a pointer to the data buffer)
bool sutsim_add_tag(const char* tag, void* data, uint32_t size, sutsim_dataType_E type);

// Subscribe to a tag (register a callback for tag updates)
bool sutsim_subscribe_to_tag(const char* tag, sutsim_TagCallback subscriber_cb);

// Write data to a tag
bool sutsim_write(const char* tag, const void* data, uint32_t size);

// Read data from the tag
bool sutsim_read(const char* tag, void* buffer, uint32_t size);

// Clean up the tag list
void sutsim_cleanup(void);
