#include <stdlib.h>
#include <string.h>

extern char *message[];
extern int quelleEstMaLangue();

char *message[] = {
  "Hello World!",
  "Bonjour le monde !"
};

int quelleEstMaLangue() {
  if (strcmp(getenv("LANG"),"fr_FR.UTF-8") == 0) {
    return 1;
  } else {
    return 0;
  }
}
