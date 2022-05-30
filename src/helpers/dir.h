#ifndef CGEN_DIR_H
#define CGEN_DIR_H

#include <sys/stat.h>

#define DEFAULT_MODE S_IRWXU

void create_dir(char *name, int mode);

void change_dir(char *name);

#endif
