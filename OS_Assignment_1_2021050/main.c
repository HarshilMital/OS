#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LEN 100
#define MAX_ARGS 20

//internal commands: cd, echo, pwd
//external commands: ls, cat,date, rm, mkdir

int status_code;
char* internal_commands[] = {"cd", "echo", "pwd", "exit", "clear"};
char* external_commands[] = {"ls", "cat", "date", "rm", "mkdir"};
char cwd[1024];

int shell_cd(char** args);
int shell_echo(char** args);
int shell_pwd(char** args);
int shell_exit();
int shell_clear();

int shell_ls(char** args);
int shell_cat(char** args);
int shell_date(char** args);
int shell_rm(char** args);
int shell_mkdir(char** args);

int (*int_cmd[5])() = {shell_cd, shell_echo, shell_pwd, shell_exit, shell_clear};
int (*ext_cmd[5])() = {shell_ls, shell_cat, shell_date, shell_rm, shell_mkdir};

char** split_line(char* line);

int shell_cd(char** args){
	if (args[1] == NULL) {
		int x = chdir(getenv("HOME"));
		return 1;
	}
	else if(strcmp(args[1], "-L") == 0){
		if (chdir(args[2]) == -1) {
			printf(" %s: no such directory\n", args[2]);
            return 1;
		}
	}
	else if(strcmp(args[1], "-P") == 0){
		if (chdir(args[2]) == -1) {
			printf(" %s: no such directory\n", args[2]);
            return 1;
		}
	}
	else{ 
		if (chdir(args[1]) == -1) {
			printf(" %s: no such directory\n", args[1]);
            return 1;
		}
	}
	return 1;
}


int shell_echo(char** args){
	if ((strcmp(args[1], "-n")) == 0){
		
		int i = 2;
		
		while(args[i] != NULL){
			printf("%s ", args[i]);
			i++;
		}
	}
	else{
		int i = 1;
		while(args[i] != NULL){
			printf("%s", args[i]);
			i++;
		}
		printf("\n");
	}
	return 1;
}

int shell_pwd(char** args){
	// printf("%s", args[1]);
	if (args[1] == NULL){
		printf("%s\n", getcwd(cwd, 1024));
	}
	else if (strcmp(args[1], "-L") == 0){
		printf("%s\n", getcwd(cwd, 1024));
	}
	else if (strcmp(args[1], "-P") == 0){
		printf("%s\n", getcwd(cwd, 1024));
	}
	else{
		printf("invalid input");
	}
	// else{
	// 	printf("invalid input!");
	// }
	return 1;
}

int shell_exit(){
	return 0;
}
int shell_clear(){
	int x = system("clear");
	return 1;
}

int shell_ls(char** args){
	int rc = fork();
	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} 
	else if (rc == 0) { // child (new process)
		char *myargs[22];
		for (int i = 1; i < 21; i++){
			myargs[i] = args[i - 1];
		}
		myargs[0] = "./shell_ls"; 
		myargs[21] = NULL;
		execvp(myargs[0], myargs);
	} 
	else { // parent goes down this path (main)
		int wc = wait(NULL);
	}
	return 1;
}

int shell_cat(char** args){
	int rc = fork();
	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} 
	else if (rc == 0) { // child (new process)
		char *myargs[22];
		for (int i = 1; i < 21; i++){
			myargs[i] = args[i - 1];
		}
		myargs[0] = "./shell_cat"; 
		myargs[21] = NULL;
		execvp(myargs[0], myargs);
	} 
	else { // parent goes down this path (main)
		int wc = wait(NULL);
	}
	return 1;
}
int shell_date(char** args){
	int rc = fork();
	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} 
	else if (rc == 0) { // child (new process)
		char *myargs[22];
		for (int i = 1; i < 21; i++){
			myargs[i] = args[i - 1];
		}
		myargs[0] = "./shell_date"; 
		myargs[21] = NULL;
		execvp(myargs[0], myargs);
	} 
	else { // parent goes down this path (main)
		int wc = wait(NULL);
	}
	return 1;
}
int shell_rm(char** args){
	int rc = fork();
	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} 
	else if (rc == 0) { // child (new process)
		char *myargs[22];
		for (int i = 1; i < 21; i++){
			myargs[i] = args[i - 1];
		}
		myargs[0] = "./shell_rm"; 
		myargs[21] = NULL;
		execvp(myargs[0], myargs);
	} 
	else { // parent goes down this path (main)
		int wc = wait(NULL);
	}
	return 1;
}
int shell_mkdir(char** args){
	int rc = fork();
	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} 
	else if (rc == 0) { // child (new process)
		char *myargs[22];
		for (int i = 1; i < 21; i++){
			myargs[i] = args[i - 1];
		}
		myargs[0] = "./shell_mkdir"; 
		myargs[21] = NULL;
		execvp(myargs[0], myargs);
	} 
	else { // parent goes down this path (main)
		int wc = wait(NULL);
	}
	return 1;
}
// char** split_line(char* line){
// 	char *token = strtok(line, " ");
// 	char* args[MAX_ARGS]; 
   
//     int i = 0;
//     while (token != NULL)
//     {
//         // printf("%s\n", token);
// 		token[strcspn(token, "\n")] = 0;
// 		args[i] = token;
//         token = strtok(NULL, " ");
// 		// token[strcspn(token, "\n")] = 0;
// 		i++;
//     }
// 	args[i] = token;
// 	return args;
// }

// char** get_args(char** line){
// 	char* args[MAX_ARGS];
// 	for (int i = 0; i < MAX_ARGS - 1; i++){
// 		args[i] = line[i + 1];
// 	}
// }
void loop(){
	status_code = 1;
	do{
		printf("HarShell> ");
		char str[MAX_LEN];
   		char* x = fgets(str, MAX_LEN, stdin);
		char** args;
		args = malloc(MAX_ARGS * sizeof(char*));
		char *token = strtok(str, " ");
   
    int i = 0;
    while (token != NULL)
    {
        
		token[strcspn(token, "\n")] = 0;
		args[i] = token;
        token = strtok(NULL, " ");
		
		i++;
    }
	args[i] = token;
		
		int flag = 1;
		for (int i = 0; i < 5; i++){
			
			if ((strcmp(args[0], internal_commands[i])) == 0){
				flag = 0;
				// printf("hey\n");
				status_code = (*int_cmd[i])(args);
				break;
			}
		}
		for (int i = 0; i < 5; i++){
			if ((strcmp(args[0], external_commands[i])) == 0){
				flag = 0;
				// printf("hey\n");
				status_code = (*ext_cmd[i])(args);
				break;
			}
		}
		if (strcmp(x, "\n") == 0){
			flag = 0;
		}
		if (flag){
			printf("command not recognized!\n");
		}
		free(args);
		
	}
    while(status_code);
}

int main(int argc, char **argv) {
	loop();
	return EXIT_SUCCESS;
}