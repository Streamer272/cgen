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

char *choose(char *question, char *answers[], int answer_count, OPTIONS *options) {
    if (options == NULL) {
        options = &(OPTIONS) {NULL, "", "", 0};
    }

    int current = options->default_index;
    char ch;

    if (options->help == NULL) {
        printf("%s\n", question);
    }
    else {
        printf("%s (%s)\n", question, options->help);
    }

    while (1) {
        for (int i = 0; i < answer_count; i++) {
            if (current == i) printf(CYAN "%s%s%s\n" RESET, options->prefix, answers[i], options->suffix);
            else printf("%s%s%s\n", options->prefix, answers[i], options->suffix);
        }

        ch = (char) getchar();
        if (ch == '\n') break;
        else if (ch == 'q') {
            current = -1;
            break;
        }

        switch (ch) {
            case 'w':
            case 'W':
            case 'k':
            case 'K':
            case 'A':
                if (current > 0) current--;
                break;
            case 's':
            case 'S':
            case 'j':
            case 'J':
            case 'B':
                if (current < answer_count - 1) current++;
                break;
            default:
                break;
        }

        printf("\r    ");
        for (int i = 0; i < answer_count; i++) {
            printf("\033[1A\r");
        }
    }

    printf("\r    ");
    int coefficient = current == -1 ? 0 : 1;
    for (int i = 0; i < answer_count + coefficient; i++) {
        printf("\033[1A\r");
    }

    if (current == -1) return NULL;
    return answers[current];
}
