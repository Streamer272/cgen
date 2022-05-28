#include "string_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* trim_string(const char* string, int length) {
    int last = 0;
    char* new;
    if ((new = malloc(sizeof(string))) == NULL) {
        perror("Couldn't allocate memory\n");
        exit(1);
    }

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
    char** array;
    if ((array = malloc(sizeof(char*) * max_take)) == NULL) {
        perror("Couldn't allocate memory\n");
        exit(1);
    }

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == split) {
            current_subarray_index++;
            if ((array[current_subarray_index] = malloc(sizeof(char*) * max_size)) == NULL) {
                perror("Couldn't allocate memory\n");
                exit(1);
            }
        }
        else {

        }
    }

    return array;
}
