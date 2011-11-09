
#include "sortieren.h"

int main(int argc, char **argv) {

    int *shuffle;
    struct timeval begin, end;
    long seconds, useconds;
    pthread_t *threads;
    struct args left, right;
    int *r;

    threads = malloc(sizeof(pthread_t)*2);
    shuffle = createRandomArray(ARRAY_SIZE);
    r = malloc(sizeof(int) * 2);

    printArray(shuffle);
    printf("\nSorting...\n\n");

    if (gettimeofday(&begin,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

    left.array = shuffle;
    right.array = shuffle;

    merge(shuffle, ARRAY_SIZE-1, r);

    left.lo = 0;
    left.hi = r[0];
    right.lo = r[1];
    right.hi = ARRAY_SIZE-1;

    pthread_create(&threads[0], NULL, threadSort, (void *) &left);
    pthread_create(&threads[1], NULL, threadSort, (void *) &right);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    if (gettimeofday(&end,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

    printArray(shuffle);

    seconds = end.tv_sec - begin.tv_sec;
    useconds = end.tv_usec - begin.tv_usec;

    if(useconds < 0) {
        useconds += 1000000;
        seconds--;
    }

    printf("Sortierdauer: %ld sec %ld ms\n\n", seconds, useconds);

    free(shuffle);
    free(threads);
    return 0;
}

void* threadSort(void *threadArgs) {
    struct args *arguments = (struct args*) threadArgs;
    quicksort(arguments->array, arguments->lo, arguments->hi);
    return NULL;
}

void printArray(int *a) {
    int i;
    for (i = 0; i<ARRAY_SIZE; ++i) {
        printf("%d\n", a[i]);
    }

}
