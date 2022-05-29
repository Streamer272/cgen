#include "generate.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include "alloc.h"
#include "string_funcs.h"
#include "exec.h"
#include "term.h"

void generate_cmake() {
    /*char *project_name = get_project_name();
    printf("name: '%s'\n", project_name);
    char *cmake_version = get_cmake_version();
    printf("version: '%s'\n", cmake_version);*/
    char *language = get_language();
    printf("language: '%s'\n", language);
    char *standard = get_language_standard(language);
    printf("standard: '%s'\n", standard);

    /*free(project_name);
    free(cmake_version);
    free(language);*/
}

char *get_project_name() {
    char *cwd = exec("/usr/bin/bash -c pwd");
    if (cwd == NULL) {
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            cwd = NULL;
        }
    }
    if (cwd != NULL) {
        char *split = get_last_split_item(cwd, '/', PATH_MAX / 4);
        free(cwd);
        cwd = split;
        split = NULL;
    }

    return ask("Enter project name", cwd);
}

char *get_cmake_version() {
    char *output = exec("/usr/bin/cmake --version");
    if (output != NULL) {
        int major, minor, patch;
        sscanf(output, "cmakeversion%d.%d.%d", &major, &minor, &patch);
        memset(output, 0, strlen(output));
        sprintf(output, "%d.%d", major, minor);
    }

    return ask("Enter cmake version", output);
}

char *get_language() {
    char *answers[] = {"C", "CXX"};
    return choose("Choose language", answers, 2, NULL);
}

char *get_language_standard(char *language) {
    if (strcmp(language, "C") == 0) {
        char *answers[] = {"90", "99", "11", "17", "23"};
        OPTIONS options = {.suffix = ""};
        options.prefix = "C";
        options.help = "if you are not sure, check out https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD.html#prop_tgt:C_STANDARD";
        options.default_index = 2;
        return choose("Choose C standard", answers, 5, &options);
    }
    else if (strcmp(language, "CXX") == 0) {
        char *answers[] = {"98", "11", "14", "17", "20", "23"};
        OPTIONS options = {.suffix = ""};
        options.prefix = "CXX";
        options.help = "if you are not sure, check out https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html";
        options.default_index = 2;
        return choose("Choose C++ standard", answers, 6, &options);
    }
    return NULL;
}
