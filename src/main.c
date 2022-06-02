#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers/def.h"
#include "helpers/colors.h"
#include "helpers/alloc.h"
#include "utils/term.h"
#include "commands/generate.h"
#include "commands/project.h"
#include "commands/build.h"
#include "commands/add.h"

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
        if (argc <= 2) {
            generate_cmake(NULL, NULL, NULL, NULL);
        }
        else {
            generate_cmake(argv[2], NULL, NULL, NULL);
        }
    }
    else if (strcmp(command, "n") == 0 || strcmp(command, "new") == 0) {
        if (argc <= 2) {
            new_project(NULL);
        }
        else {
            new_project(argv[2]);
        }
    }
    else if (strcmp(command, "b") == 0 || strcmp(command, "build") == 0) {
        build();
    }
    else if (strcmp(command, "a") == 0 || strcmp(command, "add") == 0 && argc >= 4) {
        add_dependency(argv[2], argv[3]);
    }
    else if (strcmp(command, "v") == 0 || strcmp(command, "version") == 0) {
        printf("cgen " VERSION "\n");
    }
    else {
        printf("\n");
        printf("usage: cgen COMMAND [OPTIONS]\n");
        printf("\n");
        printf("Generate CMakeLists with ease\n");
        printf("\n");
        printf("Commands:\n");
        printf("  i, init   [PROJECT]           Initialize CMakeLists\n");
        printf("  n, new    [PROJECT]           Create a new project\n");
        printf("  b, build                      Build the project\n");
        printf("  a, add    OWNER DEPENDENCY    Add a dependency to the project\n");
        printf("\n");
        printf("  v, version                    Print program version\n");
        printf("  h, help                       Show help\n");
        printf("\n");
    }

    free(command);
    return EXIT_SUCCESS;
}
