#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers/def.h"
#include "helpers/colors.h"
#include "helpers/alloc.h"
#include "utils/term.h"
#include "commands/generate.h"
#include "commands/project.h"

int main(int argc, char **argv) {
    if (strcmp(OS, "linux") != 0) {
        printf(YELLOW "cgen isn't fully cross-platform, some features may not work properly\n" RESET);
    }

    init_terminal();

    if (argc <= 1) {
        generate_cmake(NULL, NULL, NULL, NULL);
        return EXIT_SUCCESS;
    }

    char *command = alloc(malloc(sizeof(char) * 64));
    memset(command, 0, 64);
    strcat(command, argv[1]);

    if (strcmp(command, "i") == 0 || strcmp(command, "init") == 0) {
        generate_cmake(NULL, NULL, NULL, NULL);
    }
    else if (strcmp(command, "n") == 0 || strcmp(command, "new") == 0) {
        new_project(NULL);
    }
    else {
        printf("\n");
        printf("usage: cgen COMMAND [OPTIONS]\n");
        printf("\n");
        printf("Generate CMakeLists with ease\n");
        printf("\n");
        printf("Commands:\n");
        printf("  i, init\tInitialize CMakeLists\n");
        printf("  n, new\tCreate a new project\n");
        printf("  h, help\tShow help\n");
        printf("\n");
    }

    free(command);
    return EXIT_SUCCESS;
}
