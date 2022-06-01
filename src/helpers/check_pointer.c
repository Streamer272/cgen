#include "check_pointer.h"
#include <stdio.h>
#include <stdlib.h>

void *check_pointer(void *pointer) {
    if (pointer == NULL) {
        perror("Couldn't allocate memory\n");
        exit(EXIT_FAILURE);
    }
    return pointer;
}
