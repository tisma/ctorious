#include <stdio.h>

typedef struct _trampoline_data {
	void (*callback) (struct _trampoline_data*);
	void* parameters;
} trampoline_data;

void trampoline(trampoline_data* data) {
	while (data->callback != NULL)
		data->callback(data);
}

typedef struct _factorial_parameters {
	int n;
	int sum;
} factorial_parameters;

void factorial(trampoline_data* data) {
	factorial_parameters* parameters = (factorial_parameters*)data->parameters;

	if (parameters->n <= 1) {
		data->callback = NULL;
	} else {
		parameters->sum *= parameters->n;
		parameters->n--;
	}
}

int main() {
	factorial_parameters params = { 10, 1 };
	trampoline_data tramp = { &factorial, &params };

	trampoline(&tramp);

	printf("%d\n", params.sum);

	return 0;
}

