#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    sem_t *sem;
    if (argc != 3) {
        fprintf(stderr, "USAGE: %s cle valeur\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *cle = argv[1];
    int valeur = atoi(argv[2]);

    /* Création et initialisation du sémaphore */
    sem = sem_open(cle, O_CREAT, S_IRWXU, valeur);
    if (sem == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }
    printf("Initialisation OK\n");

    int sval = -1;
    /* Récupère le nombre de jetons */
    if (sem_getvalue(sem, &sval) < 0) {
        perror("sem_getvalue failed");
        exit(EXIT_FAILURE);
    }
    printf("sval = %d\n", sval);

    return EXIT_SUCCESS;
}
