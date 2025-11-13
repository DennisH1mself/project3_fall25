#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

int isAllowed(const char*cmd) {
	// TODO
	// return 1 if cmd is one of the allowed commands
	// return 0 otherwise
	for (int i = 0; i < N; i++) {
		if (strcmp(cmd, allowed[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int main() {

    // TODO
    // Add variables as needed

    char line[256];
	char *args[20]; // max 20 arguments

    while (1) {

	fprintf(stderr,"rsh>");

	if (fgets(line,256,stdin)==NULL) continue;

	if (strcmp(line,"\n")==0) continue;

	line[strlen(line)-1]='\0';

	// TODO
	// Add code to spawn processes for the first 9 commands
	// And add code to execute cd, exit, help commands
	// Use the example provided in myspawn.c

	char *token = strtok(line, " ");
	int i = 0;
	while (token != NULL) {
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	if (!isAllowed(args[0])) {
		printf("NOT ALLOWED!\n");
		continue;
	}

	if (strcmp(args[0], "exit") == 0) {
		return 0;
	} else if (strcmp(args[0], "help") == 0) {
		printf("The allowed commands are:\n");
		for (int j = 0; j < N; j++) {
			printf("%d: %s\n", j+1, allowed[j]);
		}
    } else if (strcmp(args[0], "cd") == 0) {
		if (i == 2) {
			chdir(args[1]);
		} else {
			printf("-rsh: cd: too many arguments\n");
		}
	} else {
		pid_t pid;
		posix_spawnp(&pid, args[0], NULL, NULL, args, environ) != 0

	}
    return 0;
}