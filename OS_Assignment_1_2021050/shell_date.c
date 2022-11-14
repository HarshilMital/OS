#include<stdio.h>
#include<time.h>
#include <string.h>

int main(int argc, char* argv[]){
	if (argv[2] == NULL){
		time_t tm;
    	time(&tm);
	    printf("%s", ctime(&tm));
	}
	else if(strcmp(argv[2], "-u") == 0){
		time_t now = time(&now);
		struct tm *ptm = gmtime(&now);
		printf("%s", asctime(ptm));
	}
	else{
		printf("wrong input");
	}
	return 0;
}