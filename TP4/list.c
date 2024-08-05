#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  struct node* next;
  char element[256];
};

struct node* create(char chaine[]) {
  struct node* mynode = malloc(sizeof(struct node));
  mynode->next = NULL;
  strncpy(mynode->element, chaine, 256);
  return mynode;
}

void display(struct node* n) {
  struct node* cur = n;
  do {
    printf("%s ", cur->element);
    cur = cur->next;
  } while (cur != NULL);
  printf("\n\n");
}

struct node* insert(struct node* list, char* str) {
  struct node* new_node = create(str);
  struct node* cur_node = list;
  struct node* next_node = NULL;
    
  if (list == NULL) {
    new_node->next=NULL; 
    return new_node;
  }

  next_node = cur_node->next;

  if (strcmp(cur_node->element, str) > 0) {
    new_node->next = cur_node;
    return new_node;
  }

  while(next_node && strcmp(next_node->element, str) < 0) {
    cur_node = next_node;
    next_node = next_node->next;
  }

  new_node->next = next_node;
  cur_node->next = new_node;

}
  
int main(int argc, char** argv) {
  struct node* empty = NULL;

  char a[4] = "aaa";
  char b[4] = "bbb";
  char c[4] = "ccc";
  
  empty = insert(empty, a);
  printf("OK INSERTED aaa \n\n");
  display(empty);

  empty = insert(empty, b);
  empty = insert(empty, c);

  display(empty);
  
  
  return EXIT_SUCCESS;
}
