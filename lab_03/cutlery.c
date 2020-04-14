#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int fork_knife(int counter, int assistance){
	if (counter == assistance){
		return 0;
	}
	
	int pid = fork();
	if (pid == -1){
		perror("An error occured\n");
		return 1;
	}

	if (pid == 0) {
		for(int i = 0; i < assistance; i++){
			printf("-");
		}
		printf("> current: %d | parent: %d\n", getpid(), getppid());
		sleep(1);
		fork_knife(counter, assistance+1);
		_exit(0);
	}
}

void fork_default(int counter){
	fork_knife(counter, 0);
}

int main(int argc, char*argv[]){
	
	
	int counter = -1; 
	if (argc > 1){
		counter = atoi(argv[1]);
	}
	else {
		while (counter < 0) {
			printf("Number of recursions:\n");
			scanf("%d", &counter);
		}
	}
	printf("\nmain() pid: %d\n\n", getpid());
	fork_default(counter);
	wait(NULL);
	return 0;
}
