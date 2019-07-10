#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

bool turn = true;
int counter = 0;

void* even_thread(void* arg)
{
	do
	{
		pthread_mutex_lock(&mutex);
		if (counter % 2 == 0)
		{
			pthread_cond_wait(&condition, &mutex);
		}
		fprintf(stdout, "%d\n", counter);
		fflush(stdout);
		counter++;
		pthread_cond_signal(&condition);
		pthread_mutex_unlock(&mutex);
		sleep(3);
	} while (1);
}

void* odd_thread(void* arg)
{
	do
	{
		pthread_mutex_lock(&mutex);
		if (counter % 2 != 0)
		{
			pthread_cond_wait(&condition, &mutex);
		}
		fprintf(stdout, "%d\n", counter);
		fflush(stdout);
		counter++;
		pthread_cond_signal(&condition);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	} while (1);
}

int main(int argc, char** argv)
{
	pthread_t odd_thr, even_thr;

	int rc = 0;

	rc = pthread_create(&odd_thr, NULL, odd_thread, NULL);

	if (rc < 0)
	{
		fprintf(stderr, "Error creating an odd thread! %d\n", errno);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}

	rc = pthread_create(&even_thr, NULL, even_thread, NULL);

	if (rc < 0)
	{
		fprintf(stderr, "Error creating an even thread! %d\n", errno);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}

	rc = pthread_join(odd_thr, NULL);

	if (rc < 0)
	{
		fprintf(stderr, "Error in pthread_join with odd thread! %d\n", errno);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}

	rc = pthread_join(even_thr, NULL);

	if (rc < 0)
	{
		fprintf(stderr, "Error in pthread_join with even thread! %d\n", errno);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}