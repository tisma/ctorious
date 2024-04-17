#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define M 5

int main() {
	int i, j, sem_id;
	sem_id = semget((key_t)123, N, 0666 | IPC_CREAT);
	struct sembuf sem;

	for (i = 0; i < N; i++) {
		if (fork() == 0) {
			for (j = 0; j < M; j++) {
				sem.sem_num = i;
				sem.sem_op = -1;
				sem.sem_flg = SEM_UNDO;
				semop(sem_id, &sem, 1);

				printf("%d\n", i + j * N);

				sem.sem_num = (i + 1) % N;
				sem.sem_op = 1;
				sem.sem_flg = SEM_UNDO;
				semop(sem_id, &sem, 1);
			}
			if (i == N - 1) {
				semctl(sem_id, 0, IPC_RMID);
			}
			exit(0);
		}
	}

	sem.sem_num = 0;
	sem.sem_op = 1;
	sem.sem_flg = SEM_UNDO;
	semop(sem_id, &sem, 1);
}

