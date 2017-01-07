#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>

Array* array_create(size_t size, size_t sizeof_data) {
	Array* p = (Array*)malloc(sizeof(Array));
	p->size = size;
	p->capacity = size;
	if (size) {
		p->data = malloc(size * sizeof_data);
	} else {
		p->data = NULL;
	}
	return p;
}

void array_free(Array* arr) {
	free(arr->data);
	free(arr);
}

// void array_push_back(Array* arr, int x) {
// 	arr->size++;
// 	if (arr->size >= arr->capacity) {
// 		arr->capacity = 2 * arr->size;
// 		arr->data = realloc(arr->data, arr->capacity * sizeof(int));
// 		arr->data[arr->size - 1] = x;
// 	} else {
// 		arr->data[arr->size - 1] = x;
// 	}
// }

