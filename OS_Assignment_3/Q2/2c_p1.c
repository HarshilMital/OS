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
#define BILLION 1000000000L


// sem_t *sem;
int main(int argc, char *argv[])
{

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, SHM_SIZE);

    char *ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    

    // sem = sem_open("/mysem", O_CREAT, 0666, 1);
    
    char buffer[BUFFER_SIZE];
    char string_list[50][BUFFER_SIZE];
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++) {
            buffer[j] = 'A' + rand() % 26;
        }
        strcpy(string_list[i], buffer);
    }

    double diff;
	struct timespec start, end;

	/* measure monotonic time */
	clock_gettime(CLOCK_MONOTONIC, &start);
    for (int k = 0; k < 50; k += 5){
        
        for (int i = 0; i < 5; i++){
            char buffer[BUFFER_SIZE];
            sprintf(buffer, "%s,%d",string_list[k + i],k + i);
            sprintf(ptr, "%s", buffer);
            ptr += BUFFER_SIZE + 1;
            // write(clientfd, buffer, BUFFER_SIZE);
        }
        printf("Sent 5 strings\n");
        
        // sscanf(ptr, "%s", buffer);
        // ptr += BUFFER_SIZE + 1;
        // printf("max index = %d\n", atoi(buffer));

  }

  sleep(1);
//   char buffer[BUFFER_SIZE];

  for (int k = 0; k < 10; k++){
    sscanf(ptr, "%s", buffer);
    ptr += BUFFER_SIZE + 1;
    printf("max index = %d\n", atoi(buffer));
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  diff = (BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec)/(double)BILLION;
  printf("elapsed time = %lf seconds\n", (double) diff);
    // Unmap the shared memory object and close the shared memory file descriptor
    munmap(ptr, SHM_SIZE);
    close(shm_fd);

    // Remove the shared memory object
    shm_unlink(SHM_NAME);
    

    return 0;
}
