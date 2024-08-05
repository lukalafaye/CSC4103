#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "map.h"

#define N_ITER 10
#define N_PRODUCTS 10
/* donnees generees avec http://www.mockaroo.com/
 */

struct product {
  int key;
  char product[128];
  char product_image[128];
};

struct product* find_product(FILE*f, int product_id) {
  if(fseek(f, product_id*sizeof(struct product), SEEK_SET)< 0)
    return NULL;
  struct product*p = malloc(sizeof(struct product));
  if(fread(p, sizeof(struct product), 1, f) < 1)
    return NULL;
  return p;
}

void serve_request(FILE*f, struct map*map, int product_id) {
  struct product* p = map_get(map, product_id);

  if(!p) {
    p = find_product(f, product_id);
    if(!p) {
      printf("Cannot find product #%d\n", product_id);
      return;
    }
    map_put(map, product_id, p);
  } else {
    printf("[Cached] ");
  }
  printf("Product #%d:\t%s\t%s\n", product_id, p->product, p->product_image);
}

int main(int argc, char**argv) {
  srand(time(NULL));
  FILE* f=fopen("products.dat", "r");
  struct map*map = map_init();

  for(int i=0; i<N_ITER; i++) {
    int index = rand()%N_PRODUCTS;
    serve_request(f, map, index);
  }
  fclose(f);

  return EXIT_SUCCESS;
}
