#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE 20

int main(int argc, char *argv[])
{
    // int i, num_strings, fd;
    // char **strings;
    // char buffer[BUFFER_SIZE];
    int fd1, fd2;

    // Generate the array of random strings
    // num_strings = 50;
    // strings = (char**)malloc(num_strings * sizeof(char*));
    // for (i = 0; i < num_strings; i++) {
    //     strings[i] = (char*)malloc(6 * sizeof(char));
    //     sprintf(strings[i], "str%d", i);
    // }

    char buffer[BUFFER_SIZE];
    char string_list[50][BUFFER_SIZE];
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++) {
            buffer[j] = 'A' + rand() % 26;
        }
    strcpy(string_list[i], buffer);
    // string_list[i][BUFFER_SIZE] = '\0';
    // string_list[i] = buffer;
    }

    mkfifo(FIFO_NAME, 0666);


    // Open the FIFO for writing
    

    // Send the strings to the other program
    // for (i = 0; i < 5; i++) {
    //     sprintf(buffer, "%d:%s", i, strings[i]);
    //     write(fd, buffer, BUFFER_SIZE);
    // }
    // int k = rand() % 45;
    for(int k = 0; k < 50; k += 5){
        // char buffer[BUFFER_SIZE];
        if ((fd1 = open(FIFO_NAME, O_WRONLY)) < 0) {
            fprintf(stderr, "Could not open FIFO for writing\n");
            return 1;
        }
        for (int i = 0; i < 5; i++){
            // char buffer[BUFFER_SIZE];
            sprintf(buffer, "%s,%d",string_list[k + i],k + i);
            // printf(buffer, "%s,%d",string_list[k + i],k + i);
            write(fd1, buffer, BUFFER_SIZE);
        }

        close(fd1);

        // Wait for the response from the other program
        if ((fd2 = open(FIFO_NAME, O_RDONLY)) < 0) {
            fprintf(stderr, "Could not open FIFO for reading\n");
            return 1;
        }

        read(fd2, buffer, BUFFER_SIZE);
        int max_index = atoi(buffer);
        printf("max index =  %d\n", max_index);
        close(fd2);
    }
    

    return 0;
}
