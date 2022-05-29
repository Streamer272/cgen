#include "alloc.h"
#include <stdio.h>
#include <stdlib.h>

void *alloc(void *pointer) {
    if (pointer == NULL) {
        perror("Couldn't allocate memory\n");
        exit(EXIT_FAILURE);
    }
    return pointer;
}
