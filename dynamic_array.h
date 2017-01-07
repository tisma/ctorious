#include <stdio.h>

typedef struct {
	size_t size;
	size_t capacity;
	void* data;
} Array;

// Array* array_create(size_t size, size_t sizeof_data);
void array_free(Array* arr);
void array_push_back(Array* arr, int x);

#define ARRAY_PUSH_BACK(arr, x, data_type) \
	arr->size++; \
	if (arr->size >= arr->capacity) { \
		arr->capacity = 2 * arr->size; \
		arr->data = realloc(arr->data, arr->capacity * sizeof(data_type)); \
		data_type* pp = arr->data; \
		pp[arr->size - 1] = (x); \
	} else { \
		data_type* pp = arr->data; \
		pp[arr->size - 1] = (x); \
	}