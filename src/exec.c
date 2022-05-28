#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"
#include "string_funcs.h"

char *exec(const char *command) {
    if (command == NULL) return NULL;

    FILE *process;
    char *output = alloc(malloc(sizeof(char) * 4096));
    char line[4096];

    if ((process = popen(command, "r")) == NULL) {
        perror("Couldn't execute command\n");
        exit(1);
    }
    while (fgets(line, sizeof(line), process) != NULL) {
        strcat(output, line);
    }
    pclose(process);

    char *trimmed = trim_string(output);
    free(output);
    return trimmed;
}
