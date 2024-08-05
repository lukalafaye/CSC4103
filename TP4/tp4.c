#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void squares(int* a, int* b) {
  *a = (*a)*(*a);
  *b = (*b)*(*b);
}

void display(int tab[], int taille) {
  printf("[ ");
  for (int i=0; i<taille; i++) {
    printf("%d ", tab[i]);
  }
  printf("]\n");
}

void squares_tab(int tab[], int taille) { // ok car variable passée par addresse
  for (int i=0; i<taille; i++) {
    tab[i] = tab[i]*tab[i];
  }
}

void init(int* tab, int taille) {
  for (int i=0; i<taille; i++) {
    *(tab + i) = 0;
  }
}


int string_length(const char* string) {
  char c = string[0];
  int count = 0;
  while (c != '\0') {
    count++;
    c=string[count];
    //printf("char: %c\n", c);
  }
  
  return count;
}

void string_cpy(char* dest, const char* src, size_t n) {
  printf("ok \n\n");
  for (int i=0; i<n; i++) {
    printf("dest %c src %c \n", dest[i], src[i]);
    char new = src[i];
    printf("new: %c\n", new);
    *(dest+i) = new;
  }
}

void string_concatenate(char* dest, const char* src, size_t n) {
  int dest_count = string_length(dest);
  int src_count =  string_length(src);
  for (int i=dest_count; i<(dest_count+src_count); i++) {
    dest[i] = src[i-dest_count];
  }
  dest[src_count+dest_count] = '\0';
}
		
int main(int argc, char** argv) {
  /*
  int a = 4;
  int b = 0;
  printf("a: %d &a: %p, b: %d, &b: %p \n", a, &a, b, &b);

  int *pa = &a;
  int *pb = &b;

  printf("pa: %p, &pa: %p, pb: %p, &pb: %p\n", pa, &pa, pb, &pb);
  printf("%d \n", *pa);

  *pb = 9;
  printf("a: %d, b: %d \n", a, b);

  squares(pa, pb);
  printf("After squares; a: %d, b: %d \n", a, b);

  int tab1[4] = {1, 2, 3, 4};
  display(tab1, 4);
  squares_tab(tab1, 4);
  display(tab1, 4);
  init(tab1, 4);
  display(tab1, 4); // Fonctionne car tab1 est en fait un pointeur vers tab1[0]

  int* tab2 = malloc(sizeof(int)*4);
  //display(tab2, 4);
  free(tab2);

  printf("tab1: %p, &tab1: %p, tab2: %p, &tab2 %p\n\n", tab1, &tab1, tab2, &tab2);

  printf("tab1: %lu, &tab1; %lu ,*&tab1: %lu, tab2; %lu, &tab2: %lu, *&tab2: %lu\n\n", sizeof(tab1), sizeof(&tab1), sizeof(*&tab1), sizeof(tab2), sizeof(&tab2), sizeof(*&tab2));

  int sum=0;
  printf("argv[0] is %s at %p \n", argv[0], &argv[0]);
  for (int j=1; j<argc; j++) {
    printf("argv[%d] is %s at %p \n", j, argv[j], &argv[j]);
    int val = atoi(argv[j]);
    printf("val: %d\n", val);
    sum = sum + val;
  }
  printf("Sum %d \n\n", sum);
  */
  const char* s = "abc456789";
  //int count = string_length(s);
  //printf("String: %s, Count: %d\n", s, count);

  char* v = malloc(sizeof(char)*5);
  
  string_cpy(v, s, 4);
  int count = string_length(v);
  printf("String: %s, Count: %d\n\n", v, count);


   char src[50], dest[50];

   strcpy(src, "à tous !");
   strcpy(dest,  "Bonjour");

   string_concatenate(dest, src, 15);

   printf("Final destination string : |%s|\n", dest);

   return(0);
}
