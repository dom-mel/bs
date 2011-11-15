#ifndef SORTIEREN_H
#define SORTIEREN_H

#include <stdio.h>
#include <stdlib.h>
#include "gennum.h"
#include "sortnum.h"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// laptop 547483646
#define ARRAY_SIZE 100000000

int main(int argc, char **argv);
void printArray(int a[]);
void write_numbers(int* numbers, int max, int output);
void read_numbers(int input, int* numbers);

#endif
