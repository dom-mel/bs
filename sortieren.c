
#include "sortieren.h"

int main(int argc, char **argv) {

    int *shuffel;
    struct timeval begin, end;
    long seconds, useconds;


    shuffel = createRandomArray(ARRAY_SIZE);
    printArray(shuffel);
    printf("\nSorting...\n\n");

    if (gettimeofday(&begin,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

    quicksort(shuffel, 0, ARRAY_SIZE -1) ;

    if (gettimeofday(&end,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

    printArray(shuffel);

    seconds = end.tv_sec - begin.tv_sec;
    useconds = end.tv_usec - begin.tv_usec;

    if(useconds < 0) {
        useconds += 1000000;
        seconds--;
    }
    
    printf("Sortierdauer: %ld sec %ld ms\n\n", seconds, useconds);

    free(shuffel);
    return 0;
}

void printArray(int *a) {
    int i;
    for (i = 0; i<ARRAY_SIZE; ++i) {
        printf("%12d", a[i]);
        if (i%2 == 1) {
            printf("\n");
        } else {
            printf("\t");
        }
    }
    
}
