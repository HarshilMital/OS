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


#define SHM_NAME "/my_shm"
#define SHM_SIZE 4096
#define BUFFER_SIZE 20


sem_t *sem;
int main(int argc, char *argv[])
{
    // Seed the random number generator
    // srand(time(0));

    // Create the shared memory object


    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Error creating shared memory object");
        exit(1);
    }

    // Truncate the shared memory object to the desired size
    ftruncate(shm_fd, SHM_SIZE);

    // Map the shared memory object to the process' address space
    char *ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Error mapping shared memory object");
        exit(1);
    }

    sem = sem_open("/mysem", O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
    char buffer[BUFFER_SIZE];
    char string_list[50][BUFFER_SIZE];
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++) {
            buffer[j] = 'A' + rand() % 26;
        }
        strcpy(string_list[i], buffer);
    }

    
    for (int k = 0; k < 50; k += 5){
        if (sem_wait(sem) == -1) {
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }
        for (int i = 0; i < 5; i++){
            char buffer[BUFFER_SIZE];
            sprintf(buffer, "%s,%d",string_list[k + i],k + i);
            sprintf(ptr, "%s", buffer);
            ptr += BUFFER_SIZE + 1;
            // write(clientfd, buffer, BUFFER_SIZE);
        }
        printf("Sent 5 strings\n");
        if (sem_post(sem) == -1) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }
        sleep(1);
        if (sem_wait(sem) == -1) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        sscanf(ptr, "%s", buffer);
        ptr += BUFFER_SIZE + 1;
        printf("max index = %d\n", atoi(buffer));

        if (sem_post(sem) == -1) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }
  }

  sleep(1);
//   char buffer[BUFFER_SIZE];

//   for (int k = 0; k < 10; k++){
//     sscanf(ptr, "%s", buffer);
//     ptr += BUFFER_SIZE + 1;
//     printf("max index = %d\n", atoi(buffer));
//   }
    // Unmap the shared memory object and close the shared memory file descriptor
    munmap(ptr, SHM_SIZE);
    close(shm_fd);

    // Remove the shared memory object
    shm_unlink(SHM_NAME);
    if (sem_unlink("/mysem") == -1) {
    perror("sem_unlink");
    exit(EXIT_FAILURE);
}

    return 0;
}
