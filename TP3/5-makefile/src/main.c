#include <stdlib.h>
#include <stdio.h>
#include "foo.h"
#include "tab.h"

int main(int argc, char**argv) {
  TYPE n = foo();
  printf("%d\n", n);
  return EXIT_SUCCESS;
}

// test
