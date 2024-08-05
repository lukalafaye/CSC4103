/* bits . h */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

int isPrime(int integer) {
  int isPrime = 1;
  int i = 2;
  double sqr = sqrt(integer);
  printf("sqrt = %lf\n", sqr);
  while ((isPrime == 1) && i<=sqrt(integer)) {
    if (integer%i==0) {
      isPrime = 0;
    }
    i++;
  }
  return isPrime;
}

int main ( int argc , char ** argv ) {
  uint8_t integer;
  scanf("%hhu", &integer);
  printf("Entier: %hhu\n", integer);
  int prime = isPrime(integer);
  printf("%d\n", prime);
  return EXIT_SUCCESS;
}

