#include "project.h"
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "generate.h"

void new_project(char *project_name) {
    if (project_name == NULL) project_name = get_project_name(0);

    errno = 0;
    if (mkdir(project_name, S_IRWXU) != 0) {
        switch (errno) {
            case EACCES:
                printf("Permission denied\n");
                break;
            case EEXIST:
                printf("Directory already exists\n");
                break;
            case ENAMETOOLONG:
                printf("Project name is too long\n");
                break;
        }
    }

    generate_cmake(project_name, NULL, NULL, NULL);
}
