#include <stdio.h>

extern int quelleEstMaLangue();
extern char *message[];

int main() {
  puts(message[quelleEstMaLangue()]);
  return 0;
}
