#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	if (argv[2] == NULL){
		DIR*p = opendir(".");;
		struct dirent *d;
		
		if(p == NULL){
			perror("Unable to read");
			exit(-1);
		}
		while((d = readdir(p)) != NULL){
			if (d->d_name[0] != '.'){
				printf("%s\t",d->d_name);
			}
		}
		printf("\n");
	}
	else if(strcmp(argv[2], "-a") == 0){
		DIR*p = opendir(".");;
		struct dirent *d;
		
		if(p == NULL){
			perror("Unable to read");
			exit(-1);
		}
		while((d = readdir(p)) != NULL){
			printf("%s\t",d->d_name);
		}
		printf("\n");
	}
	
	else if (strcmp(argv[2], "-m") == 0){
		DIR*p = opendir(".");;
		struct dirent *d;
		
		if(p == NULL){
			perror("Unable to read");
			exit(-1);
		}
		while((d = readdir(p)) != NULL){
			if (d->d_name[0] != '.'){
				printf("%s, ",d->d_name);
			}
		}
		printf("\n");
	}
}