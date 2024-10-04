#include "sutsim.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static sutsim_tagList_S tag_list = {0};

void sutsim_init(void) {
    tag_list.head = NULL;
    tag_list.count = 0;
    tag_list.initialized = true;
}

int sutsim_add_tag(const char* tag, void* data, uint32_t size, sutsim_dataType_E type) {
    sutsim_tagEntry_S* new_entry = (sutsim_tagEntry_S*)malloc(sizeof(sutsim_tagEntry_S));
    if (!new_entry) {
        return -1;  // Memory allocation failure
    }

    new_entry->id = tag_list.count;
    new_entry->tag = tag;
    new_entry->data = data;  // Directly use the user-provided buffer
    new_entry->size = size;
    new_entry->type = type;
    new_entry->subscriber_cb = NULL;
    new_entry->next = NULL;

    if (tag_list.head == NULL) {
        tag_list.head = new_entry;
    } else {
        sutsim_tagEntry_S* current = tag_list.head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_entry;
    }

    tag_list.count++;
    return new_entry->id;
}

void sutsim_subscribe_to_tag(const char* tag, sutsim_TagCallback subscriber_cb) {
    sutsim_tagEntry_S* current = tag_list.head;
    while (current != NULL) {
        if (strcmp(tag, current->tag) == 0) {
            current->subscriber_cb = subscriber_cb;
            return;
        }
        current = current->next;
    }
}

bool sutsim_write(const char* tag, const void* data, uint32_t size) {
    sutsim_tagEntry_S* current = tag_list.head;
    while (current != NULL) {
        if (strcmp(tag, current->tag) == 0) {
            if (size != current->size) {
                return false;  // Size mismatch
            }

            // Update the user-provided tag data buffer
            if (current->data) {
                memcpy(current->data, data, size);
            }

            if (current->subscriber_cb) {
                current->subscriber_cb(tag, data, size);
            }

            return true;
        }

        current = current->next;
    }

    return false;  // Tag not found
}

bool sutsim_read(const char* tag, void* buffer, uint32_t size) {
    sutsim_tagEntry_S* current = tag_list.head;
    while (current != NULL) {
        if (strcmp(tag, current->tag) == 0) {
            if (size != current->size) {
                return false;  // Size mismatch
            }

            // Copy the data from the tag's buffer (user-provided)
            memcpy(buffer, current->data, size);
            return true;
        }
        current = current->next;
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
    tag_list.count = 0;
}
