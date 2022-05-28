#include "generate.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "alloc.h"
#include "string_funcs.h"
#include "colors.h"
#include "exec.h"

void generate_cmake() {
    //char *project_name = get_project_name();
    //printf("name: %s\n", project_name);
    char *cmake_version = get_cmake_version();
    printf("version: '%s'\n", cmake_version);
    //free(project_name);
    free(cmake_version);
}

char *get_project_name() {
    char *cwd = exec("/usr/bin/bash -c pwd");
    char *trimmed;
    char *split = get_last_split_item(cwd, '/', PATH_MAX / 4);
    free(cwd);
    cwd = split;
    split = NULL;

    int response_size = 64;
    char *response = alloc(malloc(sizeof(char) * response_size));

    if (strlen(cwd) > 0) {
        printf("Enter project name " LIGHT_BLUE "(%s): " RESET, cwd);
        fgets(response, response_size, stdin);
        trimmed = trim_string(response);
        free(response);
        response = trimmed;
        trimmed = NULL;

        if (strcmp(response, "") == 0) {
            return cwd;
        }
        trimmed = trim_string(response);
        free(response);
        response = trimmed;
        trimmed = NULL;
        return response;
    }
    printf("Enter project name: ");
    fgets(response, response_size, stdin);
    trimmed = trim_string(response);
    free(response);
    response = trimmed;
    trimmed = NULL;
    return response;
}

char *get_cmake_version() {
    char *output = exec("/usr/bin/cmake --version");
    int major, minor, patch;
    sscanf(output, "cmakeversion%d.%d.%d", &major, &minor, &patch);
    memset(output, 0, strlen(output));
    sprintf(output, "%d.%d.%d", major, minor, patch);
    return output;
}
