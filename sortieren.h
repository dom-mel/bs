#ifndef SORTIEREN_H
#define SORTIEREN_H

#include <stdio.h>
#include "gennum.h"
#include "sortnum.h"
#include <sys/time.h>
#include <pthread.h>


// laptop 547483646
#define ARRAY_SIZE 10
#define THREAD_NUM 2

int main(int argc, char **argv);
void* threadSort(void *shuffle);
void printArray(int a[]);
struct args {
    int* array;
    short left;
};

#endif
