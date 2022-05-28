#include "string_funcs.h"
#include <string.h>
#include <malloc.h>
#include "alloc.h"

char* trim_string(const char* string, int length) {
    int last = 0;
    char* new = alloc(malloc(sizeof(string)));

    for (int i = 0; i < length; i++) {
        char current = string[i];
        if (current == '\0') break;
        if (current == ' ' || current == '\n') continue;
        new[last++] = current;
    }

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
        }
        else {
            array[current_subarray_index][current_char_index++] = string[i];
        }
    }

    return array;
}
