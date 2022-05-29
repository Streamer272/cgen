#include "term.h"
#include <string.h>
#include <malloc.h>
#include <termios.h>
#include "colors.h"
#include "alloc.h"
#include "string_funcs.h"
#include "generate.h"

void init_terminal() {
    struct termios info;
    tcgetattr(0, &info);
    info.c_lflag &= ~ICANON;
    info.c_cc[VMIN] = 1;
    info.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &info);
}

char *ask(char *question, char *default_value) {
    char *response = alloc(malloc(sizeof(char) * STDIN_INPUT_LENGTH));
    if (default_value != NULL && strlen(default_value) > 0) {
        printf("%s " LIGHT_BLUE "(%s): " RESET, question, default_value);
    } else {
        printf("%s: ", question);
    }
    fgets(response, STDIN_INPUT_LENGTH, stdin);

    if (strcmp(response, "\n") == 0 && default_value != NULL && strlen(default_value) > 0) {
        memset(response, 0, STDIN_INPUT_LENGTH);
        strcpy(response, default_value);
    }

    char *trimmed = trim_string(response);
    free(response);
    return trimmed;
}
