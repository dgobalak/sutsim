#include "sutsim.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Forward declarations */
extern void sut_init_hook(void);
extern void sut_tick_hook(void);

/* PRIVATE DATA */
static sutsim_tagList_S tag_list = {0};

/* PRIVATE FUNCTION DECLARATIONS */
static sutsim_tagEntry_S* sutsim_find_tag(const char* tag);

/* PUBLIC FUNCTIONS */
void sutsim_init(void) {
    tag_list.head = NULL;
    tag_list.tail = NULL;
    tag_list.count = 0;
    tag_list.initialized = true;

    sut_init_hook();
}

void sutsim_tick(void) {
    // TODO: Check that the simulator is initialized
    sut_tick_hook();
}

bool sutsim_add_tag(const char* tag, void* data, uint32_t size, sutsim_dataType_E type) {
    if (sutsim_find_tag(tag)) {
        return false;  // Tag already exists
    }

    sutsim_tagEntry_S* new_entry = (sutsim_tagEntry_S*)malloc(sizeof(sutsim_tagEntry_S));
    if (!new_entry) {
        return false;  // Memory allocation failure
    }

    new_entry->id            = tag_list.count;
    new_entry->tag           = tag;
    new_entry->data          = data;  // Directly use the user-provided buffer
    new_entry->size          = size;
    new_entry->type          = type;
    new_entry->subscriber_cb = NULL;
    new_entry->next          = NULL;

    if (tag_list.head == NULL) {
        tag_list.head = new_entry;
        tag_list.tail = new_entry;
    } else {
        tag_list.tail->next = new_entry;
        tag_list.tail = new_entry;
    }

    tag_list.count++;

    return true;
}

bool sutsim_subscribe_to_tag(const char* tag, sutsim_TagCallback subscriber_cb) {
    sutsim_tagEntry_S* tagEntry = sutsim_find_tag(tag);

    if (tagEntry) {
        tagEntry->subscriber_cb = subscriber_cb;
        return true;
    }

    return false;  // Tag not found
}

bool sutsim_write(const char* tag, const void* data, uint32_t size) {
    sutsim_tagEntry_S* tagEntry = sutsim_find_tag(tag);

    if (tagEntry) {
        if (size != tagEntry->size) {
            return false;  // Size mismatch
        }

        memcpy(tagEntry->data, data, size);

        if (tagEntry->subscriber_cb) {
            tagEntry->subscriber_cb(tag, data, size);
        }

        return true;
    }

    return false;  // Tag not found
}

bool sutsim_read(const char* tag, void* buffer, uint32_t size) {
    sutsim_tagEntry_S* tagEntry = sutsim_find_tag(tag);

    if (tagEntry) {
        if (size != tagEntry->size) {
            return false;  // Size mismatch
        }

        memcpy(buffer, tagEntry->data, size);
        return true;
    }

    return false;  // Tag not found
}

void sutsim_cleanup(void) {
    sutsim_tagEntry_S* current = tag_list.head;
    while (current != NULL) {
        sutsim_tagEntry_S* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    tag_list.head = NULL;
    tag_list.tail = NULL;
    tag_list.count = 0;
}

uint8_t sutsim_get_tag_type(const char* tag) {
    sutsim_tagEntry_S* tagEntry = sutsim_find_tag(tag);
    if (tagEntry) {
        return (uint8_t)tagEntry->type;
    }

    return 0;  // Tag not found
}

static sutsim_tagEntry_S* sutsim_find_tag(const char* tag) {
    sutsim_tagEntry_S* current = tag_list.head;
    while (current != NULL) {
        if (strcmp(tag, current->tag) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}
