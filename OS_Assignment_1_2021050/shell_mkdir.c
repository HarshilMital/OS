#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
	if (argv[2][0] != '-'){
		char* dirName = argv[2];
    	int rv = 0;
	
	    rv = mkdir(dirName, 0755);
	
	    if (rv != 0)
	        printf("Unable to create directory %s\n", dirName);
	}
	else if(strcmp(argv[2],"-v") == 0){
		char* dirName = argv[3];
    	int rv = 0;
	
	    rv = mkdir(dirName, 0755);
	
	    if (rv == 0)
	        printf("Directory Created: %s\n", dirName);
		else{
			printf("Unable to create directory %s\n", dirName);
		}
	}
	else{
		printf("wrong input\n");
	}
    return 0;
}