#include "string_funcs.h"
#include <string.h>
#include <malloc.h>
#include "alloc.h"

char* trim_string(const char* string) {
    int last = 0;
    char* new = alloc(malloc(sizeof(string)));
    memset(new, 0, sizeof(string));

    int i;
    for (i = 0; i < strlen(string); i++) {
        char current = string[i];
        if (current == '\0') break;
        if (current == ' ' || current == '\n') continue;
        new[last++] = current;
    }
    new[i] = '\0';

    return new;
}

char** split_string(const char *string, char split, int max_take, int max_size) {
    int current_char_index = 0;
    int current_subarray_index = 0;
    char** array = alloc(malloc(sizeof(char*) * max_take));
    array[current_subarray_index] = alloc(malloc(sizeof(char*) * max_size));

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == split) {
            array[++current_subarray_index] = alloc(malloc(sizeof(char*) * max_size));
            current_char_index = 0;
        }
        else {
            array[current_subarray_index][current_char_index++] = string[i];
        }
    }

    return array;
}
