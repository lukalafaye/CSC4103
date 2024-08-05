#include <stdio.h>
#include "tab.h"

void saisir_tab(int*tab, int size) {
  int i;
  for(i=0; i<size; i++) {
    printf("valeur ?");
    scanf("%d", &tab[i]);
  }
}

void afficher_tab(int*tab, int size) {
  int i;
  for(i=0; i<size; i++) {
    printf("%3d  ", tab[i]);
  }
  printf("\n");
}
