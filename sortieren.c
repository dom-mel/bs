
#include "sortieren.h"

int main(int argc, char **argv) {

    int *shuffle;
    struct timeval begin, end;
    long seconds, useconds;
    pthread_t *threads;
    struct args left, right;

    threads = malloc(sizeof(pthread_t)*2);

    shuffle = createRandomArray(ARRAY_SIZE);

    printArray(shuffle);
    printf("\nSorting...\n\n");

    if (gettimeofday(&begin,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

    left.array = shuffle;
    right.array = shuffle;
    left.left = 1;
    right.left = 0;

    pthread_create(&threads[0], NULL, threadSort, (void *) &left);
    pthread_create(&threads[1], NULL, threadSort, (void *) &right);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    //merge(shuffle, ARRAY_SIZE-1);
    quicksort(shuffle, 0, ARRAY_SIZE-1);

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
    if (arguments->left != 0) {
        quicksort(arguments->array, 0, ARRAY_SIZE/2);
    } else {
        quicksort(arguments->array, ARRAY_SIZE/2+1, ARRAY_SIZE-1);
    }
    return NULL;
}

void printArray(int *a) {
    int i;
    for (i = 0; i<ARRAY_SIZE; ++i) {
        printf("%d\n", a[i]);
    }

}
