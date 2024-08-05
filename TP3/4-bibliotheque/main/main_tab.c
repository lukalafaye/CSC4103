#include <stdlib.h>
#include "tab.h"

#define N 5

int main(int argc, char**argv) {
  int tab[N];
  saisir_tab(tab, N);
  afficher_tab(tab, N);
  return EXIT_SUCCESS;
}
