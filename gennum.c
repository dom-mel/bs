
#include "gennum.h"

int *createRandomArray(int size) {
    int i;
    int *fill;
    fill = (int*) malloc(sizeof(int) * size);

    if (fill == NULL) {
        return NULL;
    }

    srand((unsigned int) time(NULL));

    for (i = 0; i < size; ++i) {
        fill[i] = rand();
    }
    return fill;
}
