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

char *choose(char *question, char *answers[], int answer_count) {
    int current = 0;
    char ch;

    printf("%s\n", question);
    while (1) {
        for (int i = 0; i < answer_count; i++) {
            if (current == i) printf(CYAN "\r%s\n" RESET, answers[i]);
            else printf("\r%s\n", answers[i]);
        }

        ch = getchar();
        if (ch == '\n') break;
        else if (ch == 27) return NULL;

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

        printf("\r   ");
        printf("\033[%dA", answer_count + 0);
    }

    return answers[current];
}
