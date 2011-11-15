
#include "sortieren.h"

int main(int argc, char **argv) {

    int *shuffle;
    struct timeval begin, end;
    long seconds, useconds;
    int *r;
    int fd[2];
    pid_t pid;

    shuffle = createRandomArray(ARRAY_SIZE);

//    printArray(shuffle);
    printf("\nSorting...\n\n");

    if (gettimeofday(&begin,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

    if (pipe(fd)) {
        fprintf(stderr, "Unable to create pipe.\n");
        return 1;
    }

    r = malloc(sizeof(int) * 2);
    merge(shuffle, ARRAY_SIZE-1, r);

    pid = fork();
    if (pid == 0) {
        quicksort(shuffle, 0, r[0]);
        close(fd[0]);
        write_numbers(shuffle, r[0], fd[1]);
        return 0;
    } else if (pid > 0) {
        quicksort(shuffle, r[1], ARRAY_SIZE -1);
        close(fd[1]);
        read_numbers(fd[0], shuffle);

        if (gettimeofday(&end,(struct timezone *)0)) {
            fprintf(stderr, "can't get time\n");
            exit(1);
        }

//        printArray(shuffle);

        seconds = end.tv_sec - begin.tv_sec;
        useconds = end.tv_usec - begin.tv_usec;

        if(useconds < 0) {
            useconds += 1000000;
            seconds--;
        }

        printf("Sortierdauer: %ld sec %ld ms\n\n", seconds, useconds);

        free(shuffle);
        return 0;

    } else {
        return 2;
    }
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

void write_numbers(int* numbers, int max, int output) {
    int i;
    for (i = 0; i < max; i++) {
        int number = numbers[i];
        char string[50];
        sprintf(string, "%d\n", number);
        (void)write(output, string, strlen(string));
    }
}

void read_numbers(int input, int* numbers) {
    FILE *stream = fdopen(input, "r");
    char line[20];
    int i = 0;
    while (fgets(line, sizeof(line), stream)) {
        int number;
        sscanf(line, "%d\n", &number);
        numbers[i++] = number;
    }
    fclose (stream);
}

