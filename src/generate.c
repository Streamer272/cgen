#include "generate.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include "alloc.h"
#include "string_funcs.h"
#include "colors.h"
#include "exec.h"

void generate_cmake() {
    char *project_name = get_project_name();
    printf("name: %s\n", project_name);
    char *cmake_version = get_cmake_version();
    printf("version: '%s'\n", cmake_version);
    free(project_name);
    free(cmake_version);
}

char *get_project_name() {
    char *trimmed = NULL, *split = NULL;
    char *cwd = exec("/usr/bin/bash -c pwd");
    if (cwd == NULL) {
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            cwd = NULL;
        }
    }
    if (cwd != NULL) {
        split = get_last_split_item(cwd, '/', PATH_MAX / 4);
        free(cwd);
        cwd = split;
        split = NULL;
    }

    char *response = alloc(malloc(sizeof(char) * 64));

    if (cwd != NULL && strlen(cwd) > 0) {
        printf("Enter project name " LIGHT_BLUE "(%s): " RESET, cwd);
        fgets(response, STDIN_INPUT_LENGTH, stdin);

        if (strcmp(response, "\n") == 0) {
            return cwd;
        }
    } else {
        printf("Enter project name: ");
        fgets(response, STDIN_INPUT_LENGTH, stdin);
    }

    trimmed = trim_string(response);
    free(response);
    response = trimmed;
    trimmed = NULL;
    return response;
}

char *get_cmake_version() {
    char *output = exec("/usr/bin/cmake --version");
    if (output != NULL) {
        int major, minor, patch;
        sscanf(output, "cmakeversion%d.%d.%d", &major, &minor, &patch);
        memset(output, 0, strlen(output));
        sprintf(output, "%d.%d", major, minor);
    } else {
        output = alloc(malloc(sizeof(char) * 8));
        strcpy(output, "3.0");
    }

    return output;
}
