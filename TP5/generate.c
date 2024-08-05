#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include "student.h"

int main(int argc, char* argv[]) {
  printf("poh\n");

  if (argc != 4) {
    fprintf(stderr, "Incorrect number of parameters.\n");
    printf("Usage: ./generate in out init_grade\n");
    return EXIT_FAILURE;
  }

  char* entry_file = malloc(sizeof(char)*100);
  char* output_file = malloc(sizeof(char)*100);
  strcpy(entry_file, argv[1]);
  strcpy(output_file, argv[2]);

  uint8_t init_grade = *argv[3];

  FILE* in = fopen(entry_file, "r");
  FILE* out = fopen(output_file, "w");

  if (in==NULL) {
    printf("Problem reading %s\n", entry_file);
    printf("%s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  if (out==NULL) {
    printf("Problem reading %s\n", output_file);
    printf("%s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  char student_name[MAX_LENGTH];
  printf("ok\n");
    
  while (fgets(student_name, MAX_LENGTH, in)) {
    printf("a\n");
    printf("%s", student_name);
  }
  
}
