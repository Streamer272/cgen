#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"
#include "string_funcs.h"

char *exec(const char *command) {
    if (command == NULL) return NULL;

    FILE *process;
    char *output = alloc(malloc(sizeof(char) * 1024));
    char line[256];

    if ((process = popen(command, "r")) == NULL) {
        return NULL;
    }
    while (fgets(line, sizeof(line), process) != NULL) {
        strcat(output, line);
        memset(line, 0, sizeof(line));
    }
    pclose(process);
    process = NULL;

    char *trimmed = trim_string(output);
    free(output);
    return trimmed;
}
