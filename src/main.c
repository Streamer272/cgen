#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "os.h"
#include "colors.h"
#include "generate.h"

int main(int argc, char **argv) {
    if (strcmp(OS, "linux") != 0) {
        printf(YELLOW "cgen isn't fully cross-platform, some features may not work properly\n" RESET);
    }

    struct termios info;
    tcgetattr(0, &info);
    info.c_lflag &= ~ICANON;
    info.c_cc[VMIN] = 1;
    info.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &info);

//    char ch;
//    while ((ch = getchar()) != '\n') {
//        printf("you pressed %c (%d)\n", ch, ch);
//    }

    generate_cmake();

    return EXIT_SUCCESS;
}
