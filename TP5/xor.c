#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>


void encode(uint8_t key, FILE* in, FILE* out) {
  uint8_t buffer[512];
  uint8_t encoded[512];
  
// Read the content and print it
  printf("ok");
  int nmemb = fread(buffer, sizeof(uint8_t), 256, in);
  printf("ok");
  while(nmemb >= 1) {
    for (int i=0; i<nmemb; i++) {
      encoded[i] = buffer[i]^key;
    }
    printf("ok");
    fwrite(encoded, sizeof(uint8_t), nmemb, out);
    nmemb = fread(buffer, sizeof(uint8_t), 256, in);
    }
}

int main(int argc, char* argv[]) {

  if (argc != 4) {
    fprintf(stderr, "Incorrect number of parameters.\n");
    printf("Usage: ./encode key in out\n");
    return EXIT_FAILURE;
  }
  
  uint8_t key = atoi(argv[1]);
  printf("key: %d\n", key);  
  char* entry_file = malloc(sizeof(char)*100);
  char* output_file = malloc(sizeof(char)*100);
  strcpy(entry_file, argv[2]);
  strcpy(output_file, argv[3]);
  printf("Entry: %s\n", entry_file);  
  printf("Output: %s\n", output_file);

  printf("aa encode %s with the key %d to %s\n", entry_file, key, output_file);
  
  printf("test\n");
  
  FILE* in;
  printf("ahi\n");
  if (strcmp(argv[2], "-") == 0) {
    printf("ok\n");
    in=stdin;
  } else {
    printf("pas pos\n");
    in = fopen(entry_file, "r+");
    if (in == NULL) {
      printf("Problem reading %s\n", entry_file);
      printf("%s\n", strerror(errno));
      return EXIT_FAILURE;
    }
  }
  printf("hm\n");


  FILE* out;
  if (strcmp(argv[3], "-") == 0) {
      out=stdout;
  } else {
    out = fopen(output_file, "r+");
    if (out == NULL) {
      printf("Problem reading %s\n", output_file);
      printf("%s\n", strerror(errno));
      return EXIT_FAILURE;
    }
  }
  
  printf("hm");

  encode(key, in, out);

  
  fclose(in);
  fclose(out);
}
