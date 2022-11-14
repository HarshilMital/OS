#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	FILE* file;
    char ch;
    file = fopen(argv[2], "r");
 
    if (NULL == file) {
        printf("file can't be opened \n");
    }
 
    while (!feof(file)) {
        ch = fgetc(file);
        printf("%c", ch);
    }
    fclose(file);
    return 0;
}