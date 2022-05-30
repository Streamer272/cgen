#include "term.h"
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <termios.h>
#include "../helpers/colors.h"
#include "../helpers/alloc.h"
#include "../helpers/string_funcs.h"
#include "../commands/generate.h"

struct termios term;

void init_terminal() {
    tcgetattr(STDIN_FILENO, &term);
}

void fuck_up_terminal() {
    struct termios info;
    tcgetattr(0, &info);
    info.c_lflag &= ~ICANON;
    info.c_cc[VMIN] = 1;
    info.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &info);
}

void unfuck_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char *ask(char *question, char *default_value) {
    char *response = alloc(malloc(sizeof(char) * STDIN_INPUT_LENGTH));
    if (default_value != NULL && strlen(default_value) > 0) {
        printf("%s " LIGHT_BLUE "(%s): " RESET, question, default_value);
    } else {
        printf("%s: ", question);
    }
    fgets(response, STDIN_INPUT_LENGTH, stdin);
    unsigned long response_length = strlen(response);

    if (strcmp(response, "\n") == 0 && default_value != NULL && strlen(default_value) > 0) {
        memset(response, 0, STDIN_INPUT_LENGTH);
        strcpy(response, default_value);
    }

    char *trimmed = trim_string(response);
    free(response);

    printf("\033[1A\r%s: " GREEN "%s" RESET, question, trimmed);
    if (default_value != NULL && strlen(default_value) > 0) {
        // 5 is strlen(" (): ")
        // 2 is strlen(": ")
        for (int i = 0; i < strlen(default_value) + 5 + response_length - strlen(trimmed) - 2; i++) {
            printf(" ");
        }
    }
    printf("\n");

    return trimmed;
}

bool ask_yn(char *question, bool default_value) {
    char *response = alloc(malloc(sizeof(char) * STDIN_INPUT_LENGTH));
    char *y = default_value ? "Y" : "y";
    char *n = default_value ? "n" : "N";
    printf("%s " LIGHT_BLUE "(%s/%s): " RESET, question, y, n);
    fgets(response, STDIN_INPUT_LENGTH, stdin);

    bool return_value;
    if (strcmp(response, "\n") == 0) {
        return_value = default_value;
    } else if (strcmp(response, "y\n") == 0 || strcmp(response, "Y\n") == 0) {
        return_value = 1;
    } else if (strcmp(response, "n\n") == 0 || strcmp(response, "N\n") == 0) {
        return_value = 0;
    }

    printf("\033[1A\r%s " GREEN "%s" RESET, question, return_value ? "Yes" : "No");
    // 6 is strlen(" (y\n): ") - strlen("no")
    for (int i = 0; i < 6; i++) {
        printf(" ");
    }
    printf("\n");

    return return_value;
}

char *choose(char *question, char *answers[], int answer_count, OPTIONS *options) {
    fuck_up_terminal();

    if (options == NULL) {
        options = &(OPTIONS) {NULL, "", "", 0};
    }

    unsigned int current = options->default_index;
    bool force_quit = 0;
    char ch;

    if (options->help == NULL) {
        printf("%s\n", question);
    } else {
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
            force_quit = 1;
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
    int coefficient = force_quit == 1 ? 0 : 1;
    for (int i = 0; i < answer_count + coefficient; i++) {
        char *current_answer = alloc(malloc(sizeof(char) * STDIN_INPUT_LENGTH));
        sprintf(current_answer, "%s%s%s", options->prefix, answers[i], options->suffix);
        printf("\033[1A\r");
        for (int j = 0; j < strlen(current_answer); j++) {
            printf(" ");
        }
        printf("\r");
        free(current_answer);
    }

    if (force_quit == 1) {
        unfuck_terminal();
        return NULL;
    }

    printf("\033[1A\r%s", question);
    if (options->help != NULL) {
        printf(" (%s)", options->help);
    }
    printf(GREEN " %s%s%s\n" RESET, options->prefix, answers[current], options->suffix);

    unfuck_terminal();

    char *heap_answer = alloc(malloc(sizeof(char) * (strlen(answers[current]) + 1)));
    memset(heap_answer, 0, strlen(answers[current]) + 1);
    strcpy(heap_answer, answers[current]);
    return heap_answer;
}
