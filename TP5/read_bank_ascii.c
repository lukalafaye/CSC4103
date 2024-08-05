#include <stdlib.h>
#include <stdio.h>

int main() {
  FILE* fptr = fopen("fichier_ascii.dat", "r+");

  char line[1024];
  while(fgets(line, 1024, fptr)) {
    printf ( "Line : %s \n", line);
  }
  
  fclose(fptr);
}
