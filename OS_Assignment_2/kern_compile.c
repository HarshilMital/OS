#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <stdint.h>
#include <sched.h>

#define BILLION 1000000000L

int foo(){
	int pid1 = fork();
	// int status1, status2, status3;
	double diff1, diff2, diff3;
	struct timespec start1, end1;
	clock_gettime(CLOCK_MONOTONIC, &start1);
	if (pid1 < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} 
	else if (pid1 == 0) {
		struct sched_param param1;
		param1.sched_priority = 0;
		sched_setscheduler(getpid(), SCHED_OTHER, &param1);
		printf("1->%d\n", sched_getscheduler(getpid()));
		char *myargs1[2];
		myargs1[0] = "./hello.sh"; 
		myargs1[1] = NULL;

		execvp(myargs1[0], myargs1);
	} 
	else {
		int pid2 = fork();
		struct timespec start2, end2;
		clock_gettime(CLOCK_MONOTONIC, &start2);
		if (pid2 < 0) { // fork failed; exit
			fprintf(stderr, "fork failed\n");
			exit(1);
		} 
		else if (pid2 == 0) { // child (new process)
			struct sched_param param2;
			param2.sched_priority = 1;
			sched_setscheduler(getpid(), SCHED_RR, &param2);
			printf("2->%d\n", sched_getscheduler(getpid()));
			char *myargs1[2];
			myargs1[0] = "./hello2.sh"; 
			myargs1[1] = NULL;
			execvp(myargs1[0], myargs1);
		}
		else{
			int pid3 = fork();
			struct timespec start3, end3;
			clock_gettime(CLOCK_MONOTONIC, &start3);
			if (pid3 < 0) { // fork failed; exit
				fprintf(stderr, "fork failed\n");
				exit(1);
			} 
			else if (pid3 == 0) {
				struct sched_param param3;
				param3.sched_priority = 1;
				sched_setscheduler(getpid(), SCHED_FIFO, &param3);
				printf("3->%d\n", sched_getscheduler(getpid()));
				char *myargs1[2];
				myargs1[0] = "./hello3.sh"; 
				myargs1[1] = NULL;

				execvp(myargs1[0], myargs1);
			}
			else{
				int n = 3;
				int status;
				pid_t pid;
				while (n > 0) {
					pid = wait(&status);
					// printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
					if ((int) pid == (int) pid1){
						clock_gettime(CLOCK_MONOTONIC, &end1);
						diff1 = (BILLION * (end1.tv_sec - start1.tv_sec) + (end1.tv_nsec - start1.tv_nsec)) / (double) BILLION;
						// printf("elapsed time(1) = %lf seconds\n", (double) diff1);
						// printf("%d\n", sched_getscheduler(pid1));
					}
					else if ((int)pid == (int)pid2){
						clock_gettime(CLOCK_MONOTONIC, &end2);
						diff2 = (BILLION * (end2.tv_sec - start2.tv_sec) + (end2.tv_nsec - start2.tv_nsec)) / (double) BILLION;
						// printf("elapsed time(2) = %lf seconds\n", (double) diff2);
						// printf("%d\n", sched_getscheduler(pid2));
					}
					else if ((int)pid == (int)pid3){
						clock_gettime(CLOCK_MONOTONIC, &end3);
						diff3 = (BILLION * (end3.tv_sec - start3.tv_sec) + (end3.tv_nsec - start3.tv_nsec)) / (double) BILLION;
						// double x = diff3;
						// printf("%d\n", sched_getscheduler(pid3));
					}
					--n;
					if (n == 0){
						printf("elapsed time(1) = %lf seconds\n", (double) diff1);
						printf("elapsed time(2) = %lf seconds\n", (double) diff2);
						printf("elapsed time(3) = %lf seconds\n", (double) diff3);
					}
				}
				
				// int wc3 = waitpid(pid3, &status3, WCONTINUED);
				// clock_gettime(CLOCK_MONOTONIC, &end3);
				// double diff3 = (BILLION * (end3.tv_sec - start3.tv_sec) + (end3.tv_nsec - start3.tv_nsec)) / (double) BILLION;
				// printf("\nelapsed time(3) = %lf seconds\n", (double) diff3);
			}
			// int wc2 = waitpid(pid2, &status2, WCONTINUED);
			// clock_gettime(CLOCK_MONOTONIC, &end2);
			// double diff2 = (BILLION * (end2.tv_sec - start2.tv_sec) + (end2.tv_nsec - start2.tv_nsec)) / (double) BILLION;
			// printf("\nelapsed time(2) = %lf seconds\n", (double) diff2);
			}
		// int wc1 = waitpid(pid1, &status1, WCONTINUED);
		// clock_gettime(CLOCK_MONOTONIC, &end1);
		// double diff1 = (BILLION * (end1.tv_sec - start1.tv_sec) + (end1.tv_nsec - start1.tv_nsec)) / (double) BILLION;
		// printf("\nelapsed time(1) = %lf seconds\n", (double) diff1);
	}
	return 1;
}

int main(int argc, char* argv[]){
    foo();
    return 0;
}