#include "cmake_get.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *cmake_get(char *key) {
    FILE *cmake_file;
    if ((cmake_file = fopen("CMakeLists.txt", "r")) == NULL) {
        perror("Couldn't open CMakeLists.txt\n");
        exit(EXIT_FAILURE);
    }

    char *line;
    while ((line = fgets(line, 64, cmake_file)) != NULL) {

    }
}
