#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>


long facto(int n) {
  if ((n==0) || n ==1) {
    return 1;
  }
  return n*facto(n-1);
}

double power(double x, int n) {
  if (n==0) {
    return 1;
  }
  double res = 1;
  for (int i=0; i<n; i++) {
    res*=x;
  }
  return res;
}

double expon(double x, int n) {
  double res = 0;
  for (int i=0; i<=n; i++) {
    res += power(x, i) / facto(i);
  }
  return res;
}

void int_to_bits(int num) {
  int num_bits = sizeof(int) * 8;
  for (int i = num_bits - 1; i >= 0; i--) {
    if ((num >> i) & 1) {
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");
}
  
int main(int argc, char** argv) {
  double x = 0;
  printf("Donne valeur de x : \n");
  scanf("%lf", &x);
  
  double exp = expon(x, 20);
  printf("Resultat : %f\n", exp);
  int_to_bits(10);
  return EXIT_SUCCESS;
}
