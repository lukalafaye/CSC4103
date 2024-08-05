#include <stdlib.h>
#include <stdio.h>

#define NB_ELEMENTS 7

// TODO Definissez une fonction compar_short

// TODO Definissez une fonction compar_double

int compar_double(const void *a, const void *b) {
  double x = *(double*)a;
  double y = *(double*)b;
  return (x > y) - (x < y);
  
}

int compar_short(const void *a, const void *b) {
  short x = *(short*)a;
  short y = *(short*)b;
  return (x > y) - (x < y);
  
}

void print_tab_short(short tab[], size_t nmemb) {
  int i;
  for (i = 0 ; i < nmemb ; i++) {
    printf("tab_short[%d] = %d\n", i, tab[i]);
  }
}

void print_tab_double(double tab[], size_t nmemb) {
  int i;
  for (i = 0 ; i < nmemb ; i++) {
    printf("tab_double[%d] = %lf\n", i, tab[i]);
  }
}

void bubble_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
  


}

int main(){
  printf("3, 4 -> %d\n\n", (3>4)-(3<4));
  printf("4,3 -> %d\n\n", (4>3)-(4<3));
  printf("3, 3 -> %d\n\n", (3>3)-(3<3));


  
  short tab_short[NB_ELEMENTS] = {6, 5, 4, 3, 2, 1, 0};
  double tab_double[NB_ELEMENTS] = {7.1, 6.2, 5.3, 4.4, 3.5, 2.6, 1.7};

  printf("tab_short avant tri\n");
  print_tab_short(tab_short, NB_ELEMENTS);
  // TODO : Appelez la fonction qsort
  printf("tab_short apres tri\n");
  qsort(tab_short, NB_ELEMENTS, sizeof(short), compar_short.c);
  print_tab_short(tab_short, NB_ELEMENTS);

  // TODO : Appelez la fonction qsort
  printf("tab_double avant tri\n");
  print_tab_double(tab_double, NB_ELEMENTS);

  printf("tab_double apres tri\n");
  qsort(tab_double, NB_ELEMENTS, sizeof(double), compar_double);
  print_tab_double(tab_double, NB_ELEMENTS);

  return EXIT_SUCCESS;
}
