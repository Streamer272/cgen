#ifndef CGEN_TERM_H
#define CGEN_TERM_H

#include <stddef.h>

typedef struct {
    char *help;
    char *prefix;
    char *suffix;
    int default_index;
} OPTIONS;

void init_terminal();

void fuck_up_terminal();

void unfuck_terminal();

char *ask(char *question, char *default_value);

unsigned short ask_yn(char *question, unsigned short default_value);

char *choose(char *question, char *answers[], int answer_count, OPTIONS *options);

#endif
