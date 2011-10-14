
#include "sortieren.h"

int main(int argc, char **argv) {

    int **shuffle, i;
    struct timeval begin, end;
    long seconds, useconds;
    pthread_t *threads;

    shuffle = malloc(sizeof(int*) * THREAD_NUM);
    threads = malloc(sizeof(pthread_t) * THREAD_NUM);

    for (i = 0; i < THREAD_NUM; ++i) {
        shuffle[i] = createRandomArray(ARRAY_SIZE / THREAD_NUM);
    }

//    printArray(shuffle);
    printf("\nSorting...\n\n");

    if (gettimeofday(&begin,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

    for (i = 0; i < THREAD_NUM; ++i) {
        pthread_create(&threads[i], NULL, threadSort, shuffle[i]); 
    }

    for (i = 0; i < THREAD_NUM; ++i) {
        pthread_join(threads[i], NULL);
    }

    if (gettimeofday(&end,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

//    printArray(shuffle);

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

void* threadSort(void *shuffle) {
    quicksort(shuffle, 0, ARRAY_SIZE / THREAD_NUM -1);
    return NULL;
}

void printArray(int *a) {
    int i;
    for (i = 0; i<ARRAY_SIZE; ++i) {
        printf("%d\n", a[i]);
    }
    
}
