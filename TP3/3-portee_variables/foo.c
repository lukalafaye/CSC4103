#include <stdio.h>
#include <stdlib.h>

// Déclaration d'une variable globale
int var_globale = 1;

// Déclaration d'une variable globale statique
static int var_globale_static = 1;

// Déclaration d'une variable globale externe
extern int var_globale_extern;

int main(int argc, char**argv) {
  int i = 0;
  static int j = 0;
  printf("%d", i+j);
  int a = var_globale_extern;

  return EXIT_SUCCESS;
}
