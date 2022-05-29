#include "string_funcs.h"
#include <string.h>
#include <malloc.h>
#include "alloc.h"

char *trim_string(const char *string) {
    int last = 0;
    char *new = alloc(malloc(strlen(string) + 1));
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

char *get_last_split_item(const char *string, char split, int max_size) {
    char *item = alloc(malloc(sizeof(char) * max_size));
    memset(item, 0, sizeof(char) * max_size);
    int current = 0;

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == split) {
            memset(item, 0, sizeof(char) * max_size);
            current = 0;
        } else {
            item[current++] = string[i];
        }
    }
    item[current] = '\0';

    return item;
}
