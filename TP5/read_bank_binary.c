#include <stdlib.h>
#include <stdio.h>

int main() {
  FILE* fptr = fopen("fichier_binaire.dat", "r+");

  // Store the content of the file
  int buffer[100];

// Read the content and print it
  while(fread(buffer, sizeof(int), 1, fptr) == 1) {
    printf("%d\n", *buffer);
  }

// Close the file
  fclose(fptr); 
}
