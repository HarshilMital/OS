#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 20

int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE + 1];
    char string_list[50][BUFFER_SIZE + 1];
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 5; j++) {
            buffer[j] = 'A' + rand() % 26;
        }
    strcpy(string_list[i], buffer);
    // string_list[i][BUFFER_SIZE] = '\0';
    // string_list[i] = buffer;
  }
  for (int i = 0; i < 50; i++){
    printf("%s\n", string_list[i]);
  }
  
    return 0;
}