#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

typedef struct {
	int x;
	int y;
} Vector2i;

int main() {
	Array* arr  = array_create(0, sizeof(int));
	Array* arr2 = array_create(0, sizeof(double));
	Array* arr3 = array_create(0, sizeof(Vector2i));

	// printf("array size = %ld\n", arr->size);
	// printf("array capacity = %ld\n", arr->capacity);

	int nr_elements = 0;
	printf("How many elements you want to store? ");
	scanf("%d", &nr_elements);

	for (int i = 0; i < nr_elements; i++) {
		ARRAY_PUSH_BACK(arr, i, int);
		ARRAY_PUSH_BACK(arr2, i*i, double);
		ARRAY_PUSH_BACK(arr3, ((Vector2i){i, 2*i}), Vector2i);
	}

	// printf("array size = %ld\n", arr->size);
	// printf("array capacity = %ld\n", arr->capacity);

	((Vector2i*)arr3->data)[0].x = 333;
	((Vector2i*)arr3->data)[0].y = 888;

	for (size_t i = 0; i < arr3->size; i++) {
		Vector2i* pp = arr3->data;
		printf("(%d %d) ", pp[i].x, pp[i].y);
	}
	printf("\n");

	array_free(arr);
	array_free(arr2);
	array_free(arr3);

	return 0;
}