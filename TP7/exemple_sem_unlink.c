#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    sem_t *sem;
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s cle\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *cle = argv[1];

    if (sem_unlink(cle) < 0) {
        perror("sem_unlink failed");
        abort();
    }
    return EXIT_SUCCESS;
}
