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
    if (!tag_list.initialized) {
        return;  // Not initialized
    }

    sut_tick_hook();
}

bool sutsim_add_tag(const char* tag, void* data, uint32_t size , sutsim_dataType_E type, sutsim_TagCallback subscriber_cb, bool is_persistent) {
    if (sutsim_find_tag(tag)) {
        return false;  // Tag already exists
    }

    sutsim_tagEntry_S* new_entry = (sutsim_tagEntry_S*)malloc(sizeof(sutsim_tagEntry_S));
    if (!new_entry) {
        return false;  // Memory allocation failure
    }

    new_entry->tag = tag;
    new_entry->data = data;
    new_entry->data_size = size;
    new_entry->data_type = type;
    new_entry->subscriber_cb = subscriber_cb;
    new_entry->is_persistent = is_persistent;
    new_entry->next = NULL;

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
        if (size != tagEntry->data_size) {
            return false;  // Size mismatch
        }
        
        if (tagEntry->data) {
            memcpy(tagEntry->data, data, size);
        }

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
        if (size != tagEntry->data_size) {
            return false;  // Size mismatch
        }

        memcpy(buffer, tagEntry->data, size);
        return true;
    }

    return false;  // Tag not found
}

int8_t sutsim_get_tag_type(const char* tag) {
    sutsim_tagEntry_S* tagEntry = sutsim_find_tag(tag);
    if (tagEntry) {
        return (int8_t)tagEntry->data_type;
    }

    return -1;  // Tag not found
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
