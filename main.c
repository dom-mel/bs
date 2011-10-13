
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ARRAY_SIZE 5

int *createRandomArray(int size);

int main(int argc, char* argv) {

	int *shuffel;
	int i;

	shuffel = createRandomArray(ARRAY_SIZE);

	for (i = 0; i < ARRAY_SIZE; ++i) {
		printf("%d\n", shuffel[i]);
	}
	free(shuffel);
	

	return 0;
}


/**
 * create a array filled with random int numbers.
 *
 * @param size size of the array.
 * @return the filled array.
 */
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