#include "build.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../helpers/colors.h"
#include "../helpers/dir.h"
#include "../utils/exec.h"

void build() {
    create_dir("cgen-build", DEFAULT_MODE);
    change_dir("cgen-build");

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
