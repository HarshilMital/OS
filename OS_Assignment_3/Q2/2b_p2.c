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
    int fd1, fd2;
    char buffer[BUFFER_SIZE];

    // Open the FIFO for reading
    
    // Read the strings from the other program
    for (int k = 0; k < 10; k++){
        if ((fd1 = open(FIFO_NAME, O_RDONLY)) < 0) {
        fprintf(stderr, "Could not open FIFO for reading\n");
        return 1;
    }
        int max_index = -1;
        for (int i = 0; i < 5; i++) {
            read(fd1, buffer, BUFFER_SIZE);
            // printf("%s\n", buffer);
            char * token = strtok(buffer, ",");
            printf("%s\n", token);
            token = strtok(NULL, ",");
            int index = atoi(token);
            printf("%d\n", index);
            if (index > max_index){
                max_index = index;
            }
        }
        close(fd1);
        if ((fd2 = open(FIFO_NAME, O_WRONLY)) < 0) {
            fprintf(stderr, "Could not open FIFO for writing\n");
            return 1;
        }
        sprintf(buffer, "%d", max_index);
        write(fd2, buffer, BUFFER_SIZE);
        // printf("max index sent ")
        close(fd2);
    }
    

    

    // Send the highest index back to the other program
    

    // sprintf(buffer, "%d", highest_index);
    // write(fd, buffer, BUFFER_SIZE);
    

    return 0;
}

