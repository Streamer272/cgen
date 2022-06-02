#include "add.h"
#include <malloc.h>
#include "../helpers/alloc.h"
#include "../helpers/colors.h"
#include "../utils/exec.h"
#include "../utils/cmake_get.h"
#include "../utils/strings.h"

void add_dependency(char *owner, char *dependency) {
    char *project_name = cmake_get("project");
    rewrite_only_first_word(project_name);

    char *command = alloc(malloc(sizeof(char) * 64));
    sprintf(command, "git clone https://github.com/%s/%s.git", owner, dependency);
    char *output = exec(command);
    free(command);
    if (output == NULL) {
        printf(RED "Couldn't add dependency:\n%s\n" RESET, output);
        return;
    } else {
        free(output);
    }

    FILE *cmake_file;
    if ((cmake_file = fopen("CMakeLists.txt", "a")) == NULL) {
        printf(RED "Couldn't open CMakeLists.txt\n" RESET);
        return;
    }

    fprintf(cmake_file, "\nadd_subdirectory(%s)\ntarget_link_libraries(%s %s)\n", dependency, project_name, dependency);
    fclose(cmake_file);

    FILE *gitignore;
    if ((gitignore = fopen(".gitignore", "a")) == NULL) {
        return;
    }
    else {
        fprintf(gitignore, "\n/%s\n", dependency);
        fclose(gitignore);
    }
}
