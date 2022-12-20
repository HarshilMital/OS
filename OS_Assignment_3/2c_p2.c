#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define SHM_NAME "/my_shm"  // name of the shared memory object
#define SHM_SIZE 4096       // size of the shared memory object
#define NUM_STRINGS 50      // number of random strings
#define STRING_LEN 5        // length of each random string
#define BUFFER_SIZE 20




int main2(int argc, char *argv[])
{
    // Open the shared memory object
    sem_t *sem;

    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Error opening shared memory object");
        exit(1);
    }

    // Map the shared memory object to the process' address space
    char *ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Error mapping shared memory object");
        exit(1);
    }

    sem = sem_open("/mysem", 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    else{
        printf("hello\n");
    }

    // int max_indices[10];
    
    for(int k = 0; k < 10; k++){
        char buffer[BUFFER_SIZE];
        if (sem_wait(sem) == -1) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        int max_index = -1;
        for (int i = 0; i < 5; i++) {
            // read(sockfd, buffer, BUFFER_SIZE);

            sscanf(ptr, "%s", buffer);
            ptr += BUFFER_SIZE + 1;
            char * token = strtok(buffer, ",");
            printf("%s\n", token);
            token = strtok(NULL, ",");
            int index = atoi(token);
            printf("%d\n", index);
            if (index > max_index){
                max_index = index;
            }
        }
        
        sprintf(buffer, "%d", max_index);
        sprintf(ptr, "%s", buffer);
        ptr += BUFFER_SIZE + 1;

        if (sem_post(sem) == -1) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }
        // max_indices[k] = max_index;

        // sprintf(max_indices[k], "%d", max_index);
        // write(sockfd, buffer, BUFFER_SIZE);
  }

//   char buffer[BUFFER_SIZE];
//   for (int k = 0; k < 10; k++){
//         sprintf(buffer, "%d", max_indices[k]);
//         sprintf(ptr, "%s", buffer);
//         ptr += BUFFER_SIZE + 1;
//   }
        
    // Write the highest index back to the shared memory
    // sprintf(ptr, "%d", highest_index);

    // Unmap the shared memory object and close the shared memory file descriptor
    munmap(ptr, SHM_SIZE);
    close(shm_fd);

    return 0;
}
