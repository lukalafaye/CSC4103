#include <stdio.h>
#include <stdlib.h>

int var_globale = 1;
static int var_globale_static = 2;
extern int var_globale_extern = 3;

int main(int argc, char**argv) {
  static int a = 0;
  int b = 0;
  printf("Somme : %d", a+b);
  printf("Somme2 : %d", var_globale+var_globale_static+var_globale_extern);
  return EXIT_SUCCESS;
}
