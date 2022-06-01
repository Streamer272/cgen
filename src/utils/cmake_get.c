#include "cmake_get.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helpers/alloc.h"
#include "../helpers/def.h"

char *cmake_get(char *key) {
    FILE *cmake_file;
    if ((cmake_file = fopen("CMakeLists.txt", "r")) == NULL) {
        perror("Couldn't open CMakeLists.txt\n");
        exit(EXIT_FAILURE);
    }

    int key_index = 0;
    bool record = false;
    char ch;
    char *value = alloc(calloc(1024, sizeof(char)));
    memset(value, 0, 1024);
    while ((ch = (char) fgetc(cmake_file)) != EOF) {
        if (record && ch != '(' && ch != ')') {
            strncat(value, &ch, 1);
        }

        if (ch == '(') continue;
        if (record && ch == ')') break;
        if (ch == key[key_index]) {
            key_index++;
            if (key_index == strlen(key)) {
                record = true;
                key_index = 0;
            }
        }
        else {
            key_index = 0;
        }
    }

    fclose(cmake_file);
    return value;
}
