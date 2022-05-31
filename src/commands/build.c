#include "build.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../helpers/colors.h"
#include "../helpers/dir.h"
#include "../utils/exec.h"
#include "../utils/cmake_get.h"

void build() {
//    char *project_name = cmake_get("project");
//    printf("proj '%s'\n", project_name);
//    return;

    DIR *dir = opendir(BUILD_PATH);
    if (dir == NULL) {
        create_dir(BUILD_PATH, DEFAULT_MODE);
    }
    else {
        closedir(dir);
    }

    change_dir(BUILD_PATH);

    printf("Running " BOLD "cmake .." RESET "\n");
    if (exec("cmake ..") == NULL) {
        perror("Couldn't run " BOLD "cmake" RESET "\n");
        exit(EXIT_FAILURE);
    }

    printf("Running " BOLD "make" RESET "\n");
    if (exec("make") == NULL) {
        perror("Couldn't run " BOLD "make" RESET "\n");
        exit(EXIT_FAILURE);
    }

    change_dir("..");
    printf("Your executable is located in " BOLD "cgen-build/" RESET "\n");
}
