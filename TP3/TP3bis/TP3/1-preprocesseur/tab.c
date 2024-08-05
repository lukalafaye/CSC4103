#include <stdio.h>
#include "types.h"
#include "tab.h"

void saisir_tab(struct tableau*tab) {
  int i;
  for(i=0; i<tab->size; i++) {
    printf("valeur ?");
    scanf("%d", &tab->values[i]);
  }
}

void afficher_tab(struct tableau*tab) {
  int i;
  for(i=0; i<tab->size; i++) {
    printf("%3d  ", tab->values[i]);
  }
  printf("\n");
}
