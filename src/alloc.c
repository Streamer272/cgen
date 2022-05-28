#include "alloc.h"
#include <stdio.h>
#include <stdlib.h>

void *alloc(size_t size) {
    void* pointer;
    if ((malloc(size)) == NULL) {
        perror("Couldn't allocate memory\n");
        exit(1);
    }
    return pointer;
}
