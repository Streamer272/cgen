#include "dir.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void create_dir(char *name, int mode) {
    errno = 0;
    if (mkdir(name, S_IRWXU) == 0) {
        return;
    }

    switch (errno) {
        case EACCES:
            perror("Permission denied\n");
            break;
        case EEXIST:
            perror("Directory already exists\n");
            break;
        case ENAMETOOLONG:
            perror("Project name is too long\n");
            break;
    }

    exit(EXIT_FAILURE);
}

void change_dir(char *name) {
    errno = 0;
    if (chdir(name) == 0) {
        return;
    }

    switch (errno) {
        case EACCES:
            perror("Permission denied\n");
            break;
        case ENOENT:
            perror("Directory doesn't exist\n");
            break;
    }

    exit(EXIT_FAILURE);
}
