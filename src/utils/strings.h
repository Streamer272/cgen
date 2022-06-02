#ifndef CGEN_STRINGS_H
#define CGEN_STRINGS_H

char *trim_string(const char *string);

char *get_last_split_item(const char *string, char split, int max_size);

void rewrite_only_first_word(char *string);

#endif
