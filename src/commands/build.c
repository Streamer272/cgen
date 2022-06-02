#include "build.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../helpers/colors.h"
#include "../helpers/dir.h"
#include "../utils/exec.h"
#include "../utils/cmake_get.h"
#include "../utils/strings.h"

void build() {
    char *project_name = cmake_get("project");
    rewrite_only_first_word(project_name);

    DIR *dir = opendir(BUILD_PATH);
    if (dir == NULL) {
        create_dir(BUILD_PATH, DEFAULT_MODE);
    }
    else {
        closedir(dir);
    }

    printf("Building " BOLD "%s" RESET "\n", project_name);

    change_dir(BUILD_PATH);

    printf("Running " BOLD "cmake .." RESET "\n");
    char *output = exec("cmake ..");
    if (output == NULL) {
        perror("Couldn't run " BOLD "cmake" RESET "\n");
        exit(EXIT_FAILURE);
    }
    else {
        free(output);
    }

    printf("Running " BOLD "make" RESET "\n");
    output = exec("make");
    if (output == NULL) {
        perror("Couldn't run " BOLD "make" RESET "\n");
        exit(EXIT_FAILURE);
    }
    else {
        free(output);
    }

    change_dir("..");
    printf("Your executable is located in " BOLD "cgen-build/%s" RESET "\n", project_name);
}
