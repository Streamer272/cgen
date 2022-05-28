#include "generate.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "alloc.h"
#include "string_funcs.h"

void generate_cmake() {
    char *project_name = get_project_name();
    printf("Project name is '%s'\n", project_name);
    free(project_name);
}

char *get_project_name() {
    char *cwd = alloc(malloc(sizeof(char) * PATH_MAX));
    FILE *f;
    char path[PATH_MAX];
    if ((f = popen("/usr/bin/bash -c pwd", "r")) == NULL) {
        perror("Couldn't get current working directory\n");
        exit(1);
    }
    while (fgets(path, sizeof(path), f) != NULL) {
        strcat(cwd, path);
    }
    pclose(f);
    char *trimmed = trim_string(cwd);
    free(cwd);
    cwd = trimmed;
    trimmed = NULL;
    char* split = get_last_split_item(cwd, '/', PATH_MAX / 4);
    free(cwd);
    cwd = split;
    split = NULL;

    int response_size = 64;
    char *response = alloc(malloc(sizeof(char) * response_size));

    if (strlen(cwd) > 0) {
        printf("Enter project name (%s): ", cwd);
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
