#include "project.h"
#include <stddef.h>
#include <sys/stat.h>
#include "../helpers/dir.h"
#include "generate.h"

void new_project(char *project_name) {
    if (project_name == NULL) project_name = get_project_name(0);
    create_dir(project_name, DEFAULT_MODE);
    change_dir(project_name);
    generate_cmake(project_name, NULL, NULL, NULL);
}
