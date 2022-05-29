#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "os.h"
#include "colors.h"
#include "generate.h"
#include "term.h"

int main(int argc, char **argv) {
    if (strcmp(OS, "linux") != 0) {
        printf(YELLOW "cgen isn't fully cross-platform, some features may not work properly\n" RESET);
    }

    init_terminal();

    generate_cmake();

    return EXIT_SUCCESS;
}
