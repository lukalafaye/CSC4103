#include <stdio.h>

int main() {
    int nombre_octets;
    int nombre_blocs;

    printf("Entrez le nombre d'octets : ");
    scanf("%d", &nombre_octets);

    // Calcul du nombre de blocs nécessaires
    nombre_blocs = (nombre_octets + 7) / 8;

    printf("Nombre de blocs de 8 octets nécessaires : %d\n", nombre_blocs);

    return 0;
}
