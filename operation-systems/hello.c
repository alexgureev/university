#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// number of commands
#define COMMANDS_SIZE 12

int filedes[COMMANDS_SIZE][2];

void close_descriptors();
void pipe_descriptors();
void exec_command(int des, char** command);

// closes all file descriptors
void close_descriptors() {
	int i;
	for(i = 0; i<COMMANDS_SIZE; i++) {
		close(filedes[i][0]);
		close(filedes[i][1]);
	}
}

// create descriptors
void pipe_descriptors() {
	int i;
	for(i = 0; i<COMMANDS_SIZE; i++) {
		pipe(filedes[i]);
	}
}

// execute command, reads and writes into pipes
void exec_command(int des, char** command) {
	if(des < COMMANDS_SIZE - 1) {
		dup2(filedes[des][1], 1);
	}

	if (des > 0) {
		dup2(filedes[des-1][0], 0);
	}

	close_descriptors();
	execvp(command[0], command);
	exit(EXIT_FAILURE);
}

void main() {
	pipe_descriptors();
	int status, i;
	pid_t pids[COMMANDS_SIZE];

	// commands list for each child
	char *commands[][4] = {
		{"awk", "{print $1,$4}", "log.txt"},
		{"cut", "-d:", "-f1"},
		{"sh", "-c", "tr -d ["},
		{"sort"},
		{"uniq"},
		{"awk", "{print $2}"},
		{"sort"},
		{"uniq", "-c"},
		{"sort", "-nr"},
		{"head"},
		{"awk", "{total += $1; rs[$2] = $1 } END { for (r in rs) print r, rs[r], rs[r]*100/total\"%\" }"},
		{"sort", "-nr", "-k2"}
	};

	// create forks for each command	
	for(i = 0; i<COMMANDS_SIZE; i++) {
		pids[i] = fork();
		if (!pids[i]) { 
	        exec_command(i, commands[i]);
		} else if (pids[i] == -1) {
			fprintf(stderr, "Can't fork, exiting...\n");
			exit(EXIT_FAILURE);
		}
	}

	// close descriptors in parent process
	close_descriptors();

	// wait for all childs
	for(i = 0; i<COMMANDS_SIZE; i++) {
		if(i < COMMANDS_SIZE - 1) {
			waitpid(pids[i], NULL, 0);
		} else {
			waitpid(pids[i], &status, 0);
		}
	}

	exit(status);
}