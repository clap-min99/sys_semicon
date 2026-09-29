#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>

#include "msg.h"

pid_t pid;

int main(int argc, char **argv)
{
	int ret;
	int id_msg;
	struct msg_buf msgbuf;

	if(argc != 2) {
		printf("usage: %s {file name}\n", argv[0]);
		return EXIT_FAILURE;
	}
	printf("[%d] running %s %s\n", pid = getpid(), argv[0], argv[1]);

	if(strlen(argv[1]) >= MAX_FNAME) {
		printf("[%d] error: maximum file length is %d\n", pid, MAX_FNAME);
		return EXIT_FAILURE;
	}

	/* Implement code */

	id_msg = msgget((key_t)KEY_MSG, 0666|IPC_CREAT);
	if(id_msg == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	msgbuf.mtype = MTYPE_C2S;
	strcpy(msgbuf.fname, argv[1]);
	msgbuf.pid = pid;

	ret = msgsnd(id_msg, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), 0);
	if(ret == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	ret = msgrcv(id_msg, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), pid, 0);
	if(ret == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	if(msgbuf.valid) {
		printf("[%d] %s: size=%ld, mode=%o\n", pid, argv[1], msgbuf.size, msgbuf.mode);
	}
	else {
		printf("[%d] %s: not found\n", pid, argv[1]);
	}
	
	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}

