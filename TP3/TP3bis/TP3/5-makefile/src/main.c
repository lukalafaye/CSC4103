#include <stdlib.h>
#include <stdio.h>
#include "foo.h"
#include "tab.h"

int main(int argc, char**argv) {
  TYPE n = foo();
  printf("%d\n", n);
  int tab[3] = {0, 1};
  int size = 3;
  saisir_tab(tab, size);
  afficher_tab(tab, size);
  return EXIT_SUCCESS;
}

// ok
