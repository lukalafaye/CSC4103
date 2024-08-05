#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>

int main(int argc, char** argv) {
  if(argc != 2) {
    fprintf(stderr, "usage: %s n\n", argv[0]);
    return EXIT_FAILURE;
  }

  int n = atoi(argv[1]);

  printf("n: %d\n", n);

  sem_t* sem = sem_open("/cpt", O_CREAT, S_IRWXU, 4);

  sem_unlink("/cpt");

  for(int i=0; i<n; i++)
    fork();

  sem_wait(sem);

  printf("[%d] start job\n", getpid());
  sleep(1);
  printf("[%d] stop job\n", getpid());

  sem_post(sem);

  return EXIT_SUCCESS;
}
