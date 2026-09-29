#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

pid_t pid;

int main(int argc, char **argv)
{
	pid_t pid_temp;	
	int i;
	int num_of_child;
	int status;
	pid_t pid_wait;

	printf("[%d] running %s", pid = getpid(), argv[0]);
	for(i=1; i<argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");

	num_of_child = argc - 2;

	for (i = 0; i < num_of_child; i++) {
		pid_temp = fork();
		if (pid_temp == 0) {                                      // 자식만
			pid = getpid();
			printf("[%d] about to run [grep -rn %s %s]\n", pid, argv[i + 2], argv[1]);
			execlp("grep", "grep", "-rn", argv[i + 2], argv[1], NULL);
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}

	printf("[%d] waiting child's termination\n", pid);            // 부모, 한 번만

	for (i = 0; i < num_of_child; i++) {
		pid_wait = wait(&status);
		printf("[%d] pid %d has been terminated with status %d\n", pid, pid_wait, WEXITSTATUS(status));
	}

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}