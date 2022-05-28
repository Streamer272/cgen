#ifndef CGEN_STRING_FUNCS_H
#define CGEN_STRING_FUNCS_H

char* trim_string(const char* string);
char** split_string(const char* string, char split, int max_take, int max_size);

#endif
