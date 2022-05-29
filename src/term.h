#ifndef CGEN_TERM_H
#define CGEN_TERM_H

void init_terminal();

char *ask(char *question, char *default_value);

char* choose(char *question, char *answers[], int answer_count);

#endif
