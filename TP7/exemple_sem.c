#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

int main(int argc, char **argv) {
    sem_t *sem;
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s cle\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *cle = argv[1];

    /* Création et initialisation du sémaphore */
    sem = sem_open(cle, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    printf("Ouverture OK\n");
    printf("On prend un jeton ...\n");
    sem_wait(sem);
    printf("Jeton obtenu.\n");
    sleep(5);
    printf("On relâche le jeton\n");
    sem_post(sem);
    printf("Jeton relâché\n");
    return EXIT_SUCCESS;
}
