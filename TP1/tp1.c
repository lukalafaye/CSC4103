#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double power2(double val, int n) {
  double res = 1.0;
  for (int i=0; i<n; i++) {
    res *= val;
    printf("val = %f \n", val);
  }
  return res;
}

double expon(double x, int n) {
  printf("x = %f", x);
  
  double sum = 0;
  for (int j=0; j<n; j++) {
    sum += power2(x, j) / facto(j);
    printf("j = %d, x=%f \n", j, x);
  //   printf("facto %d \n", facto(j));
    printf("power %f \n", power2(x, j));
    printf("%f\n", sum);
  }

  return sum;
}

unsigned int int_to_bits(unsigned n) {
  if (n==0) {
    return 0;
  } 
  if (n == 1) {
    return 1;
  }
  return (n%2) + 10*int_to_bits(n/2);
}

int facto(int n) {
  if (n == 0) {
    return 1;
  }
  if (n==1) {
    return 1;
  } else {
    return n*facto(n-1);
  }
}


int main(void) {
  printf("Hello World\n");

  int nombre;
 // scanf("%d", &nombre);
  printf("Nombre: %d \n\n", nombre);

  int d = 2;
  while ((nombre%d != 0) && (d<=sqrt(nombre))) {
    d = d+1;
  }

  bool isPrime;;
  
  if (d>sqrt(nombre)) {
    isPrime = true;
  } else {
    isPrime = false;
  }
  
  printf("Le nombre est premier? 0 pour faux, 1 pour vrai : %d\n\n", isPrime);
  
  int valeur_a_trouver = rand() % 100;
/*
  int i = 0;
  nombre = -1;
  
  while ((i<10) && (nombre != valeur_a_trouver)) {
    printf("Essaie un nouveau nombre : \n");
    scanf("%d", &nombre);
    i++;
  }
*/
  nombre = facto(0);
  double nombre2 = power2(0, 5);
  printf("5! = %d\n", nombre);
  printf("2^5 = %f \n", nombre2);

  printf("Donne nombre x : \n");

  // 8
//  scanf("%f", &nombre2);
  nombre2 = 3;

  nombre2 = expon(nombre2, 20);

  printf("exp(x) = %f \n", nombre2);
  printf("%d", int_to_bits(10));
  return 0;
}
