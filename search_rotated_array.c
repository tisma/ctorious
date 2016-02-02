#include <stdio.h>
#include <stdlib.h>

int array[] = { 5, 6, 7, 8, 9, 1, 2, 3, 4 };

unsigned int search(int arr[], int key, unsigned int low, unsigned int high)
{
	unsigned int mid = (low + high) / 2;

	if (low > high)
		return -1;

	if (arr[mid] == key)
		return mid;

	if (arr[low] <= arr[mid]) {
		if (arr[low] <= key && arr[mid] >= key) {
			return search(arr, key, low, mid - 1);
		} else {
			return search(arr, key, mid + 1, high);
		}
	} else {
		if (arr[mid] <= key && arr[high] >= key) {
			return search(arr, key, mid + 1, high);
		} else {
			return search(arr, key, low, mid - 1);
		}
	}

	return -1;
}

void print_array(int arr[], int size)
{
	int i = 0;
	for (i = 0; i < size; i++) {
		printf("arr[%d]=%d ", i, arr[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	int i, n = 0, x = 0;

	if (argc == 2) {
		n = atoi(argv[1]);
	}

	print_array(array, sizeof(array) / sizeof(int));

	if (argc != 2) {
		printf("Enter number to search: ");
		scanf("%d", &n);
	}

	x = search(array, n, 0, sizeof(array) / sizeof(int) - 1);
	if (x == -1) {
		printf("No element found\n");
	} else {
		printf("Found at index: %d\n", x);
	}

	return EXIT_SUCCESS;
}

