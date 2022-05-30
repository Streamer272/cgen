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

void generate_cmake(char *project_name, char *cmake_version, char *language, char *language_standard) {
    if (project_name == NULL) project_name = get_project_name(1);
    if (cmake_version == NULL) cmake_version = get_cmake_version();
    if (language == NULL && (language = get_language()) == NULL) return;
    if (language_standard == NULL && (language_standard = get_language_standard(language)) == NULL) return;
    bool create_main = ask_yn("Create main.c?", 1);
    bool continue_ = ask_yn("Is this ok?", 1);
    if (!continue_) {
        printf("Abort\n");
        return;
    }

    FILE *cmake_file;
    if ((cmake_file = fopen("CMakeLists.txt", "w")) == NULL) {
        perror("Couldn't create CMakeLists.txt\nCopy the following text and paste it to CMakeLists.txt\n\n");
        cmake_file = stdout;
    }

    fprintf(cmake_file, "cmake_minimum_required(VERSION %s)\n", cmake_version);
    fprintf(cmake_file, "project(%s %s)\n", project_name, language);
    fprintf(cmake_file, "\n");
    fprintf(cmake_file, "set(CMAKE_%s_STANDARD %s)\n", language, language_standard);
    fprintf(cmake_file, "\n");
    fprintf(cmake_file, "add_executable(%s\n\tmain.c)\n", project_name);

    if (cmake_file != stdout) fclose(cmake_file);

    if (create_main) {
        FILE *main_file;
        if ((main_file = fopen("main.c", "w")) == NULL) {
            perror("Couldn't create main.c\n");
            exit(EXIT_FAILURE);
        }

        fprintf(main_file, "#include <stdio.h>\n");
        fprintf(main_file, "#include <stdlib.h>\n");
        fprintf(main_file, "\n");
        fprintf(main_file, "int main(int argc, char **argv) {\n");
        fprintf(main_file, "\tprintf(\"Hello, world!\\n\");\n");
        fprintf(main_file, "\n");
        fprintf(main_file, "\treturn EXIT_SUCCESS;\n");
        fprintf(main_file, "}\n");

        fclose(main_file);
    }

    free(project_name);
    free(cmake_version);
    free(language);
    free(language_standard);
}

char *get_project_name(bool use_default) {
    if (!use_default) return ask("Enter project name", NULL);

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
        options.help = "if you are not sure, select C11";
        options.default_index = 2;
        return choose("Choose C standard", answers, 5, &options);
    } else if (strcmp(language, "CXX") == 0) {
        char *answers[] = {"98", "11", "14", "17", "20", "23"};
        OPTIONS options = {.suffix = ""};
        options.prefix = "CXX";
        options.help = "if you are not sure, select CXX14";
        options.default_index = 2;
        return choose("Choose C++ standard", answers, 6, &options);
    }
    return NULL;
}
