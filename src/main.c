#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "string_funcs.h"

char* get_project_name();
void generate_cmake();

int main() {
    generate_cmake();

    return EXIT_SUCCESS;
}

void generate_cmake() {
    char* project_name = get_project_name();
    printf("Project name is '%s'\n", project_name);
    free(project_name);
}

char* get_project_name() {
    char* cwd;
    if ((cwd = malloc(sizeof(char) * PATH_MAX)) == NULL) {
        perror("Couldn't allocate memory\n");
        exit(1);
    }
    FILE* f;
    char path[PATH_MAX];
    if ((f = popen("/usr/bin/bash -c pwd", "r")) == NULL) {
        perror("Couldn't get current working directory\n");
        exit(1);
    }
    while (fgets(path, sizeof(path), f) != NULL) {
        strcat(cwd, path);
    }
    pclose(f);
    printf("full output: '%s'\n", cwd);
    char* trimmed = trim_string(cwd, PATH_MAX);
    printf("trimmed: '%s'\n", trimmed);
    free(cwd);
    cwd = trimmed;

    int response_size = 64;
    char* response;
    if ((response = malloc(sizeof(char) * response_size)) == NULL) {
        perror("Couldn't allocate memory\n");
        exit(1);
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Enter project name (Blank for %s): ", cwd);
        fgets(response, response_size, stdin);
        if (strcmp(response, "") == 0) {
            return cwd;
        }
        else {
            return response;
        }
    }
    else {
        printf("Enter project name: ");
        fgets(response, response_size, stdin);
        return response;
    }
}
